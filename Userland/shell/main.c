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

	
	init_shell();
	putc('\n');
	putc('a');
	print_commands();
	init_shell();
	while(1){
		update_shell();
	}
	putc('a');
	return 0;
}