#include <stdio.h>
#include <libc.h>
#include <string.h>

void fputc(int fd, char c)
{
	write(fd, &c, 1);
}

void putc(char c)
{
	fputc(STDOUT, c);
}

int fputsn(int fd, char * c, int n)
{
	return write(fd, c, n);
}

int fputs(int fd, char * c)
{
	return write(fd, c, strlen(c));
}

int puts(char * c)
{
	return fputs(STDOUT, c);
}