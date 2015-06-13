#include <stdio.h>
#include <shell.h>
#include <stdint.h>
#include <stdlib.h>

int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	init_shell();

	while (1) {
		update_shell();
	}

	return 0;
}
