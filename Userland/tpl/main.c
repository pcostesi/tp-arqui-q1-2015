#include <stdio.h>
#include <stdlib.h>


int main(unsigned int pcount, char * pgname[], void * pgptrs[]) {
	unsigned int cur;

    printf("Loading %d module%s.\n", pcount, pcount == 1 ? "" : "s");
	for (cur = 0; cur < pcount; cur++) {
		printf("Module #%d - <%s> at %x\n", cur, pgname[cur], pgptrs[cur]);
	}
    
    return 0;
}