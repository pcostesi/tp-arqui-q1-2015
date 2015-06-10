#ifndef __LIBC
#define __LIBC 1

/* common structs */
struct rtc_time 
{
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
	unsigned char mon;
	unsigned char year;
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
extern int ioctl(unsigned int fd, unsigned long request, void * params);

#define IOCTL_MOVE 0
#define IOCTL_CLR 1
#define IOCTL_SET_COLOR 2
#define _IOCTL_HIGH_LOW(high, low)	((((high) & 0xFF) << 8) | ((low) & 0xFF))

#define IOCTL_CURSOR(row, pos)	_IOCTL_HIGH_LOW((row), (pos))
#define IOCTL_COLOR(fore, back)	_IOCTL_HIGH_LOW((fore), (back))


enum IOCTL_COLOR_CODE
{
	IOCTL_COLOR_BLACK = 0,
	IOCTL_COLOR_BLUE,
	IOCTL_COLOR_GREEN,
	IOCTL_COLOR_CYAN,
	IOCTL_COLOR_RED,
	IOCTL_COLOR_MAGENTA,
	IOCTL_COLOR_BROWN,
	IOCTL_COLOR_LIGHT_GRAY,

	IOCTL_COLOR_GRAY = 8,
	IOCTL_COLOR_LIGHT_BLUE,
	IOCTL_COLOR_LIGHT_GREEN,
	IOCTL_COLOR_LIGHT_CYAN,
	IOCTL_COLOR_LIGHT_RED,
	IOCTL_COLOR_LIGHT_MAGENTA,
	IOCTL_COLOR_YELLOW,
	IOCTL_COLOR_WHITE,
};

#endif