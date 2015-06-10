#include <stdio.h>
#include <shell.h>
#include <stdint.h>
#include <stdlib.h>

char * asd = "Hola esto es un string largo para que se rompa en algun lugar, se pise con algo y el resto salgan bien";

int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	unsigned int cur;
	char fmt[] = "Module #%d - <%s> at %x\n";
	char greeting[] = "Loading %d modules.\n";

	printf(greeting, pcount);
	for (cur = 0; cur < pcount; cur++) {
		printf(fmt, cur, pgname[cur], pgptrs[cur]);
	}

	
	putc('\n');
	init_shell();

	while(1){
		update_shell();
	}
	putc('a');
	return 0;
}