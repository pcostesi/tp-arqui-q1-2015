#include <stdio.h>
#import <shell.h>

int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	int i = 10000;
	unsigned int cur;
	char fmt[] = "Module #%d - <%s> at %x\n";
	char greeting[] = "Loading %d modules.\n";

	printf(greeting, pcount);
	for (cur = 0; cur < pcount; cur++) {
		printf(fmt, cur, pgname[cur], pgptrs[cur]);
	}
	//init_shell();
	while(i-->0){
		putc('a');
	}
	return 0;
}