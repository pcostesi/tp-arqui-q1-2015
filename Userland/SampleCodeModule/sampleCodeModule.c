#include <libc.h>
#include <string.h>
#include <stdio.h>

int banana(int a) {
	return 2 * a;
}

int main() {
	struct rtc_time timestruct;
	//halt();
	//pause();
	char str[] = "hi %d %x %o \n";
	char ts[] = "time is %d:%d:%d.";
	printf(str, 15, 15, 15);
	gettime(&timestruct);
	ioctl(STDOUT, IOCTL_MOVE, IOCTL_CURSOR(12, 20));
	ioctl(STDOUT, IOCTL_SET_COLOR, IOCTL_COLOR(IOCTL_COLOR_GREEN, IOCTL_COLOR_YELLOW));
	printf(ts, timestruct.hour, timestruct.min, timestruct.sec);
	return 0xDEADBEEF;
}