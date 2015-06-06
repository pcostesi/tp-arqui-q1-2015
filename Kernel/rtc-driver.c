#include <stdint.h>	
#include <rtc-driver.h>
#include <io.h>


unsigned get_rtc_seconds()
{
	return get_rtc_crt(RTC_STATS_MASK_SEC);
}

unsigned get_rtc_minutes()
{
	return get_rtc_crt(RTC_STATS_MASK_MIN);
}


unsigned get_rtc_hours()
{
	return get_rtc_crt(RTC_STATS_MASK_HOURS);
}


unsigned get_rtc_day_of_week()
{
	return get_rtc_crt(RTC_STATS_MASK_DAY_OF_WEEK);
}


unsigned get_rtc_day_of_month()
{
	return get_rtc_crt(RTC_STATS_MASK_DAY_OF_MONTH);
}


unsigned get_rtc_month()
{
	return get_rtc_crt(RTC_STATS_MASK_MONTH);
}


unsigned get_rtc_year()
{
	return get_rtc_crt(RTC_STATS_MASK_YEAR);
}

unsigned get_rtc_crt(enum RTC_STATS_MASK cmd)
{
	outportb((unsigned)RTC_CMD_PORT, (unsigned)cmd);
	return	inportb((unsigned) RTC_DATA_PORT);

}


void set_rtc_seconds(uint8_t  seconds)
{
	set_rtc_crt(RTC_STATS_MASK_SEC, seconds);
}

void set_rtc_minutes(uint8_t minutes)
{
	set_rtc_crt(RTC_STATS_MASK_MIN, minutes);
}


void set_rtc_hours(uint8_t hours)
{
	set_rtc_crt(RTC_STATS_MASK_HOURS, hours);
}

void set_rtc_day_of_week(uint8_t dow)
{
	set_rtc_crt(RTC_STATS_MASK_DAY_OF_WEEK, dow);
}


void set_rtc_day_of_month(uint8_t dom)
{
	set_rtc_crt(RTC_STATS_MASK_DAY_OF_MONTH, dom);
}


void set_rtc_month(uint8_t month)
{
	set_rtc_crt(RTC_STATS_MASK_MONTH, month);
}


void set_rtc_year(uint8_t year)
{
	set_rtc_crt(RTC_STATS_MASK_YEAR, year);
}

void set_rtc_crt(enum RTC_STATS_MASK cmd, uint8_t data)
{
	outportb((unsigned)RTC_CMD_PORT, (unsigned)cmd);
	outportb((unsigned)RTC_DATA_PORT, (unsigned)data);
}
