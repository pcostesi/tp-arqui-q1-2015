#include <stdio.h>
#import <shell.h>

int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	unsigned int cur;
	char fmt[] = "Module #%d - <%s> at %x\n";
	char greeting[] = "Loading %d modules.\n";

	printf(greeting, pcount);
	for (cur = 0; cur < pcount; cur++) {
		printf(fmt, cur, pgname[cur], pgptrs[cur]);
	}
	
	//init_shell();
	int i = 100000000;
	putc('a');
	while(i-->0){
	}
	return 0;
}