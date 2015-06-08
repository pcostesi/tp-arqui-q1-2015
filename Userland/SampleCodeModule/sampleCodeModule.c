#include <libc.h>
#include <string.h>


int main() {
	struct rtc_time timestruct;
	//halt();
	//pause();
	char str[] = "hi \n";
	char ts[5];
	write(1, str, 4);
	write(1, str, 4);
	write(1, str, 4);
	write(1, str, 4);
	gettime(&timestruct);
	itoa(timestruct.hour, ts);
	write(1, ts, 2);
	write(1, ":", 1);
	itoa(timestruct.min, ts);
	write(1, ts, 2);
	write(1, ":", 1);
	itoa(timestruct.sec, ts);
	write(1, ts, 2);
	return 0xDEADBEEF;
}