#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

static unsigned int read_fmt(int fd, int c, va_list ap);

static int read_str(int fd, char * str);
static int read_base_10(int fd, int * n);


int scanf(char * fmt, ...)
{
	va_list ap;
	int read;
	
	va_start(ap, fmt);
	read = vfscanf(STDIN, fmt, ap);
	va_end(ap);
	return read;
}

int fscanf(int fd, char * fmt, ...)
{
	va_list ap;
	int read;
	
	va_start(ap, fmt);
	read = vfscanf(fd, fmt, ap);
	va_end(ap);
	return read;
}


int vfscanf(int fd, char * fmt, va_list ap)
{
	int c;
	char * ptr = fmt;
	int in_fmt = 0;
	int read = 0;
	int last;

	while ((c = *ptr++) != (char) 0) {
		if (in_fmt) {
			if (!read_fmt(fd, c, ap)) {
				return read;
			}
			read++;
			in_fmt = 0;
		} else if (c == '%') {
			in_fmt = 1;
			continue;
		} else if (last == '\n') {
			return read;
		}

		while ((last = fgetc(fd)) == ' ');
	}
	return read;
}

static unsigned int read_fmt(int fd, int c, va_list ap)
{
	int read = 0;
	char * ptr;

	switch (c) {
		case 's':
		read = read_str(fd, va_arg(ap, char *));
		break;

		case 'd':
		read = read_base_10(fd, va_arg(ap, int *));
		break;

		case 'c':
		read = 1;
		ptr = va_arg(ap, char *);
		(*ptr) = fgetc(fd);
		fputc(STDOUT, *ptr);
		break;

		default:
		return read;
	}
	fputc(STDOUT, '\n');
	return read;
}

static int read_str(int fd, char * str)
{
	char c;
	int idx = 0;
	while (idx < SCANF_MAX_STR_BUFFER - 1) {
		c = (char) fgetc(fd);
		if (c == ' ' || c == '\n') {
			break;
		}
		fputc(STDOUT, c);
		str[idx++] = c;
	}
	str[idx] = 0;
	return idx > 0;
}

static int read_base_10(int fd, int * n)
{
	char c;
	int idx = 0;
	uint64_t asd = 0;
	while (idx < 9) {
		c = (char) fgetc(fd);
		fputc(STDOUT, c);
		if (c < '0' || c > '9' || asd >= (UINT64_MAX / 9)) {
			fungetc(fd, c);
			break;
		} else {
			asd = asd * 10 + c - '0';
			idx++;	
		}
	}
	*n = (int) asd;
	return idx > 0;
}



int atoi(char * str)
{
	char c;
	int i = 0;
	while ((c = *str++) != 0) {
		if (c < '0' || c > '9') {
			break;
		}
		i = i * 10 + c - '0';
	}
	return i;
}