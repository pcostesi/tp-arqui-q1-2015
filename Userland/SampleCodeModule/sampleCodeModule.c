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
	char ts[] = "time is %d:%d:%d.\n";
	printf(str, 15, 15, 15);
	gettime(&timestruct);
	printf(ts, timestruct.hour, timestruct.min, timestruct.sec);
	return 0xDEADBEEF;
}