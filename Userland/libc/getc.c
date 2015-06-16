#include <stdio.h>
#include <libc.h>
#include <stdint.h>

static int unchar = -1;

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
	int has_data = 0;
	if (unchar != -1) {
		c = (char) unchar;
		unchar = -1;
		return c;
	}

	do {
		has_data = read(fd, &c, 1) != -1;
	} while (!has_data);
	return c;
}

int getc(void)
{
	return fgetc(STDIN);
}

int fgetsn(int fd, char * c, int n)
{
	int has_read = 0;
	if (unchar != -1 && n > 1) {
		(*c) = (char) unchar;
		c++;
		has_read++;
		unchar = -1;
	}
	unchar = -1;
	return has_read + read(fd, c, n - has_read);
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