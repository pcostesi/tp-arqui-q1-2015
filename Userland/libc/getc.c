#include <stdio.h>
#include <libc.h>

static unsigned char unchar = '\0';

void fungetc(int fd, char c) {
	if (fd == STDIN) {
		unchar = c;
	}
}

void ungetc(char c) {
	fungetc(STDIN, c);
}

int fgetc(int fd)
{
	char c;
	if (unchar != '\0') {
		c = unchar;
		unchar = '\0';
		return c;
	}

	do {
		read(fd, &c, 1);
	} while (c == 0);
	return c;
}

int getc(void)
{
	return fgetc(STDIN);
}

int fgetsn(int fd, char * c, int n)
{
	if (unchar != '\0' && n > 1) {
		(*c) = unchar;
		n--;
		c++;
		unchar = '\0';
	}
	return read(fd, c, n);
}

int fgets(int fd, char * c, unsigned int n)
{
	char buffer;
	char idx = 0;
	while (idx < n && (buffer = fgetc(fd)) != '\n') {
		*c++ = buffer;
		idx++;
	}
	return idx;
}

int gets(char * c, unsigned int n)
{
	return fgets(STDIN, c, n);
}