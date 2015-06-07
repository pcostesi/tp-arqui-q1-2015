#include <libc.h>

int main() {
	//halt();
	pause();
	char str[] = "hi mothafuckas";
	write(1, str, 14);
	return 0xDEADBEEF;
}
