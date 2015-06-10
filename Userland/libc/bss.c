#include <stdlib.h>
#include <stdint.h>

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void __init_bss(void)
{
	memset(&bss, 0, &endOfBinary - &bss);
}