#include <stdio.h>
#include <stdarg.h>

static unsigned int read_number(int fd, va_list ap, int c);
static unsigned int read_escape(int fd, char c);

static int read_str(int fd, char ** str);
static int read_base(int fd, int * n, int base);


int scanf(char * fmt, ...)
{
	va_list ap;
	int read;
	
	va_start(ap, fmt);
	read = vfscanf(STDOUT, fmt, ap);
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

	while ((c = *ptr++) != (char) 0) {
		if (in_fmt) {
			switch (in_fmt) {
				case '%':
				read += read_number(fd, ap, c);
				break;

				case '\\':
				read += read_escape(fd, c);
				break;

				default:
				return read;
			}
			in_fmt = 0;
			continue;		
		}

		if (c == '%' || c == '\\') {
			in_fmt = c;
		} else if (c >= 0){
			if (fgetc(fd) != c) {
				return read;
			}
		}
	}
	return read;
}


static unsigned int read_escape(int fd, char c)
{
	switch (c) {
		case 'n':
		return fgetc(fd) == '\n';
		break;
		
		case 'b':
		return fgetc(fd) == '\b';
		break;
		
		case '\\':
		return fgetc(fd) == '\n';
		break;

		default:
		return 0;
	}
	return 1;
}


static unsigned int read_number(int fd, va_list ap, int c)
{
	int read = 0;

	switch (c) {
		case 's':
		read = read_str(fd, va_arg(ap, char **));
		break;

		case 'd':
		read = read_base(fd, va_arg(ap, int *), 10);
		break;

		case 'o':
		read = read_base(fd, va_arg(ap, int *), 8);
		break;

		case 'x':
		read = read_base(fd, va_arg(ap, int *), 16);
		break;

		default:
		return read;
	}
	return read;
}

static int read_str(int fd, char ** str)
{
	char c;
	int idx = 0;
	while ((c = fgetc(fd)) != ' ' && idx < SCANF_MAX_STR_BUFFER) {
		(*str)[idx++] = c;
	}

	return idx > 0;
}

static int read_base(int fd, int * n, int base)
{
	char c;
	int idx = 0;
	int code;
	while ((c = fgetc(fd)) != ' ' && idx < SCANF_MAX_STR_BUFFER) {
		code = c - (base > 10 ? (c < 'A' ? '0' : 'A') : '0');
		if (code > base || code < 0) return 0;
		(*n) = (*n) * base + code;
	}

	return idx > 0;
}