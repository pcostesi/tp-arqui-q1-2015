#ifndef __LIBC
#define __LIBC 1

/* common structs */
struct rtc_time 
{
	int sec;
	int min;
	int hour;
	int mday;
	int mon;
	int year;
};

/* syscalls */
extern void gettime(struct rtc_time *);
extern void settime(struct rtc_time *);
extern int write(unsigned int fd, char * str, unsigned int size);
extern void pause(void);
extern int read(unsigned int fd, char * str, unsigned int size);
extern void halt(void);
extern void shutdown(void);
extern void towel(void);


#endif