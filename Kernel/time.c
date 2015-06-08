#include <rtc-driver.h>
#include <stdint.h>
#include <time.h>


#define error1 "Invalid time seconds & minutes must be between 0 & 60, and hours must be between 0 & 24"
#define error2 "Invalid date"
//*Time functions*//

int isleapyear(int year){
	return ((!(year%4) && (year%100)) || !(year%400));
}

int valid_time(int sec, int min, int hrs){

	if( sec >60 || sec < 0	||
		min >60 || min < 0	||
		hrs >24 || sec < 0)
	{
		return 0;
	}
	return 1;

}
//1 valid, 0 invalid
int valid_date(int year, int month, int day){
	unsigned short monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 0 || month < 0 || year < 0 || month > 12){
		return 0;
	}
	if (isleapyear(year) && month == 2) {
		monthlen[1]++;
	}
	if (day>monthlen[month-1]) {
		return 0;
	}
	return 1;
}


//int syscalls
void syscall_get_time(struct rtc_time * time)
{
	time->sec 	= get_rtc_seconds();
	time->min 	= get_rtc_minutes();
	time->hour	= get_rtc_hours();
	time->mon	= get_rtc_month();
	time->year	= get_rtc_year();
}

void syscall_set_time(struct rtc_time * time)
{
	set_rtc_seconds((uint8_t) time->sec);
	set_rtc_minutes((uint8_t) time->min);
	set_rtc_hours((uint8_t) time->hour);
	set_rtc_month((uint8_t) time->mon);
	set_rtc_year((uint8_t) time->year);
}