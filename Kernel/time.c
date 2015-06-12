#include <rtc-driver.h>
#include <stdint.h>
#include <time.h>

// taken from https://www.kernel.org/pub/linux/kernel/people/marcelo/linux-2.4/arch/m68k/bvme6000/rtc.c
// the url says Marcelo, so it must be bug-free.
#define BCD2BIN(val) (((val)&15) + ((val)>>4)*10)
#define BIN2BCD(val) ((((val)/10)<<4) + (val)%10)

#define error1 "Invalid time seconds & minutes must be between 0 & 60, and hours must be between 0 & 24"
#define error2 "Invalid date"
//*Time functions*//

int isleapyear(unsigned char year){
	return ((!(year%4) && (year%100)) || !(year%400));
}

int valid_time(unsigned char sec, unsigned char min, unsigned char hrs){

	if( sec >60 || sec < 0	||
		min >60 || min < 0	||
		hrs >24 || sec < 0)
	{
		return 0;
	}
	return 1;

}
//1 valid, 0 invalid
int valid_date(unsigned char year, unsigned char month, unsigned char day){
	unsigned short monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 0 || month < 1 || year < 0 || month > 12){
		return 0;
	}
	if (isleapyear(year) && month == 2) {
		monthlen[1]++;
	}
	if (day>monthlen[month-1] || day < 1) {
		return 0;
	}
	return 1;
}

// see http://wiki.osdev.org/CMOS
//int syscalls
void syscall_get_time(struct rtc_time * time)
{
	uint8_t registerB = get_rtc_crt(RTC_STATS_MASK_STATUS_REGISTER_B);

	unsigned char sec 	= get_rtc_seconds();
	unsigned char min 	= get_rtc_minutes();
	unsigned char hour	= get_rtc_hours();
	unsigned char mon	= get_rtc_month();
	unsigned char year	= get_rtc_year();
	unsigned char day	= get_rtc_day_of_month();

    // Convert BCD to binary values if necessary
	if (!(registerB & 0x04)) {
	    sec 	= BCD2BIN(sec);
	    min 	= BCD2BIN(min);
	    hour 	= BCD2BIN(hour);
	    day 	= BCD2BIN(day);
	    mon 	= BCD2BIN(mon);
	    year 	= BCD2BIN(year);
	}

	// Convert 12 hour clock to 24 hour clock if necessary

	if (!(registerB & 0x02) && (hour & 0x80)) {
	    hour = ((hour & 0x7F) + 12) % 24;
	}

	time->sec 	= sec;
	time->min 	= min;
	time->hour	= hour;
	time->mon	= mon;
	time->year	= year;
	time->day	= day;
}

void syscall_set_time(struct rtc_time * time)
{
	uint8_t registerB = get_rtc_crt(RTC_STATS_MASK_STATUS_REGISTER_B);

	unsigned char sec 	= time->sec;
	unsigned char min 	= time->min;
	unsigned char hour	= time->hour;
	unsigned char mon	= time->mon;
	unsigned char year	= time->year;
	unsigned char day	= time->day;

    // Convert binary to BCD values if necessary
	if (!(registerB & 0x04)) {
	    sec 	= BIN2BCD(sec);
	    min 	= BIN2BCD(min);
	    hour 	= BIN2BCD(hour);
	    day 	= BIN2BCD(day);
	    mon 	= BIN2BCD(mon);
	    year 	= BIN2BCD(year);

	}

	// Convert 12 hour clock to 24 hour clock if necessary
	if (!(registerB & 0x02) && (hour & 0x80)) {
	    hour = ((hour & 0x7F) + 12) % 24;
	}

	set_rtc_seconds(sec);
	set_rtc_minutes(min);
	set_rtc_hours(hour);
	set_rtc_month(mon);
	set_rtc_year(year);
	set_rtc_day_of_month(day);
}