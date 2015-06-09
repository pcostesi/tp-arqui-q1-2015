#include <stdio.h>
#include <libc.h>

int fgetc(int fd)
{
	char c;
	read(fd, &c, 1);
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
	char buffer;
	char idx = 0;
	while (idx < n && (buffer = fgetc(fd) != '\n')) {
		*c++ = buffer;
		idx++;
	}
	return idx;
}

int gets(char * c, unsigned int n)
{
	return fgets(STDIN, c, n);
}