#ifndef __TIME_H_ 
#define __TIME_H_ 1

#include <stdint.h>

struct rtc_time 
{
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
	unsigned char mon;
	unsigned char year;
};

void syscall_get_time(struct rtc_time *);
void syscall_set_time(struct rtc_time *);
int isleapyear(unsigned char year);
int valid_time(unsigned char sec, unsigned char min, unsigned char hour);
int valid_date(unsigned char year, unsigned char month, unsigned char day);

#endif