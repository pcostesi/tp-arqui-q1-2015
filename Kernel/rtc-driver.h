//getters
uint16_t get_rtc_seconds();
uint16_t get_rtc_minutes();
uint16_t get_rtc_hours();
uint16_t get_rtc_day_of_week();
uint16_t get_rtc_day_of_month();
uint16_t get_rtc_month();
uint16_t get_rtc_year();
uint16_t get_rtc_crt(RTC_STATS_MASK cmd);

//Setters
void set_rtc_seconds(uint8_t  seconds);
void set_rtc_minutes(uint8_t minutes);
void set_rtc_hours(uint8_t hours);
void set_rtc_day_of_week(uint8_t dow);
void set_rtc_day_of_month(uint8_t dom);
void set_rtc_month(uint8_t month);
void set_rtc_year(uint8_t year);
void set_rtc_crt(RTC_STATS_MASK cmd, uint8_t data);