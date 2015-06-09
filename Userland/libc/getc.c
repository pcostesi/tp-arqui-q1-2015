#include <stdio.h>
#include <libc.h>
#include <string.h>

int fgetc(int fd)
{
	char c;
	write(fd, &c, 1);
	return c;
}

int getc(void)
{
	return fgetc(STDIN);
}

int fgetsn(int fd, char * c, int n)
{
	return read(fd, c, n);
}

int fgets(int fd, char * c, unsigned int n)
{
	return read(fd, c, n);
}

int gets(char * c, unsigned int n)
{
	return fgets(STDIN, c, n);
}