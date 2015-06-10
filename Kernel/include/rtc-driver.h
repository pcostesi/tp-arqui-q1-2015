#ifndef __rtcdriver
#define __rtcdriver 1

#include <stdint.h>

#define RTC_CMD_PORT 	0x70
#define RTC_DATA_PORT	0x71


enum RTC_STATS_MASK 
{
	RTC_STATS_MASK_SEC					=	0x00,
	RTC_STATS_MASK_SEC_ALARM			=	0x01,
	RTC_STATS_MASK_MIN					=	0x02,
	RTC_STATS_MASK_MIN_ALARM			=	0x03,
	RTC_STATS_MASK_HOURS				=	0x04,
	RTC_STATS_MASK_HOURS_ALARM			=	0x05,
	RTC_STATS_MASK_DAY_OF_WEEK			=	0x06,
	RTC_STATS_MASK_DAY_OF_MONTH			=	0x07,
	RTC_STATS_MASK_MONTH				=	0x08,
	RTC_STATS_MASK_YEAR					=	0x09,
	RTC_STATS_MASK_STATUS_REGISTER_A	=	0x0A,
	RTC_STATS_MASK_STATUS_REGISTER_B	=	0x0B,
	RTC_STATS_MASK_STATUS_REGISTER_c	=	0x0C,
	RTC_STATS_MASK_STATUS_REGISTER_D	=	0x0D,
	RTC_STATS_MASK_DIAGNOSTIC			=	0x0E,
	RTC_STATS_MASK_SHUTDOWN_STATUS		=	0x0F,

};

//getters
unsigned get_rtc_seconds();
unsigned get_rtc_minutes();
unsigned get_rtc_hours();
unsigned get_rtc_day_of_week();
unsigned get_rtc_day_of_month();
unsigned get_rtc_month();
unsigned get_rtc_year();
unsigned get_rtc_crt(enum RTC_STATS_MASK cmd);

//Setters
void set_rtc_seconds(uint8_t seconds);
void set_rtc_minutes(uint8_t minutes);
void set_rtc_hours(uint8_t hours);
void set_rtc_day_of_week(uint8_t dow);
void set_rtc_day_of_month(uint8_t dom);
void set_rtc_month(uint8_t month);
void set_rtc_year(uint8_t year);
void set_rtc_crt(enum RTC_STATS_MASK cmd, uint8_t data);

#endif