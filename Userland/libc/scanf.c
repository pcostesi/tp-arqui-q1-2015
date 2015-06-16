#include <stdio.h>
#include <stdarg.h>

static unsigned int read_fmt(int fd, va_list ap, int c);

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
		while ((last = fgetc(fd)) == ' ');
		if (in_fmt) {
			fungetc(fd, last);
			if (!read_fmt(fd, ap, c)) {
				return read;
			}
			read++;
			in_fmt = 0;
		} else if (c == '%') {
			in_fmt = c;
			continue;
		} else if (last == '\n') {
			return read;
		}
	}
	return read;
}

static unsigned int read_fmt(int fd, va_list ap, int c)
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
		fputc(STDERR, *ptr);
		break;

		default:
		return read;
	}
	return read;
}

static int read_str(int fd, char * str)
{
	char c;
	int idx = 0;
	while (idx < SCANF_MAX_STR_BUFFER - 1) {
		c = fgetc(fd);
		fputc(STDERR, c);
		if (c == ' ' || c == '\n') {
			break;
		}
		str[idx++] = c;
	}
	str[idx] = 0;
	return idx > 0;
}

static int read_base_10(int fd, int * n)
{
	char c;
	int idx = 0;
	while (idx < 10) {
		c = fgetc(fd);
		fputc(STDERR, c);
		if (c < '0' || c > '9') {
			break;
		}
		(*n) = (*n) * 10 + c - '0';
		idx++;
	}
	fungetc(fd, c);
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