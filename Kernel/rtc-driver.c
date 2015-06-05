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



uint16_t get_rtc_seconds()
{
	outportb(70h, RTC_STATS_MASK_SEC);
	return	(unit16_t )inportb(71h);
}

uint16_t get_rtc_minutes()
{
	outportb(70h, RTC_STATS_MASK_MIN);
	return	(unit16_t )inportb(71h);
}


uint16_t get_rtc_hours()
{
	outportb(70h, RTC_STATS_MASK_HOURS);
	return	(unit16_t )inportb(71h);
}


uint16_t get_rtc_day_of_week()
{
	outportb(70h, RTC_STATS_MASK_DAY_OF_WEEK);
	return	(unit16_t )inportb(71h);
}


uint16_t get_rtc_day_of_month()
{
	outportb(70h, RTC_STATS_MASK_DAY_OF_MONTH);
	return	(unit16_t )inportb(71h);
}


uint16_t get_rtc_month()
{
	outportb(70h, RTC_STATS_MASK_MONTH);
	return	(unit16_t )inportb(71h);
}


uint16_t get_rtc_year()
{
	outportb(70h, RTC_STATS_MASK_YEAR);
	return	(unit16_t )inportb(71h);
}

unit16_t get_rtc_crt(RTC_STATS_MASK cmd)
{
	outportb(70h, cmd);
	return	(unit16_t )inportb(71h);

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

void set_rtc_crt(RTC_STATS_MASK cmd, uint8_t data)
{
	outportb(70h, cmd);
	outportb(71h, data);
}
