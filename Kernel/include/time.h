#ifndef __TIME_H_ 
#define __TIME_H_ 1

#include <stdint.h>

struct rtc_time 
{
	int sec;
	int min;
	int hour;
	int mday;
	int mon;
	int year;
};

void syscall_get_time(struct rtc_time *);
void syscall_set_time(struct rtc_time *);
int isleapyear(int year);
int valid_time(int sec, int min, int hour);
int valid_date(int year,int month,int day);

#endif