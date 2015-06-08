#include <stdio.h>
#include <stdarg.h>

static int print_str(int fd, char * str);
static int print_dec(int fd, int n);
static int print_oct(int fd, int n);
static int print_hex(int fd, int n);
static int print_to_base(int value, char * buffer, int base);

int printf(char * fmt, ...)
{
	va_list ap;
	int written;
	
	va_start(ap, fmt);
	written = vfprintf(STDOUT, fmt, ap);
	va_end(ap);
	return written;
}

int fprintf(int fd, char * fmt, ...)
{
	va_list ap;
	int written;
	
	va_start(ap, fmt);
	written = vfprintf(fd, fmt, ap);
	va_end(ap);
	return written;
}

int print_escape(int fd, char c)
{
	switch (c) {
		case 'n':
		fputc(fd, '\n');
		break;
		
		case 'b':
		fputc(fd, '\b');
		break;
		
		case '\\':
		fputc(fd, '\\');
		break;

		default:
		fputc(fd, c);
	}
	return 1;
}

int print_number(int fd, va_list ap, char c)
{
	int written = 0;

	switch (c) {
		case 's':
		written = print_str(fd, va_arg(ap, char *));
		break;

		case 'd':
		written = print_dec(fd, va_arg(ap, int));
		break;

		case 'o':
		written = print_oct(fd, va_arg(ap, int));
		break;

		case 'x':
		written = print_hex(fd, va_arg(ap, int));
		break;

		default:
		fputc(fd, c);
		written++;
	}
	return written;
}

int vfprintf(int fd, char * fmt, va_list ap)
{
	char c;
	char * ptr = fmt;
	int in_fmt = 0;
	int written = 0;

	while ((c = *ptr++) != (char) 0) {

		if (in_fmt) {
			switch (in_fmt) {
				case '%':
				written += print_number(fd, ap, c);
				break;

				case '\\':
				written += print_escape(fd, c);
				break;
			}
			in_fmt = 0;
			continue;
		}

		if (c == '%' || c == '\\') {
			in_fmt = c;
		} else {
			fputc(fd, c);
			written++;
		}
	}

	return written;
}

static int print_str(int fd, char * str)
{
	int count = 0;
	char c;
	while ((c = *str++) != 0) {
		fputc(fd, c);
		count++;
	}
	return count;
}

static int print_dec(int fd, int n)
{
	int count;
	char buffer[20];
	count = print_to_base(n, buffer, 10);
	return fputsn(fd, buffer, count);
}

static int print_oct(int fd, int n)
{
	int count;
	char buffer[20];
	count = print_to_base(n, buffer, 8);
	return fputsn(fd, buffer, count);
}

static int print_hex(int fd, int n)
{
	int count;
	char buffer[20];
	count = print_to_base(n, buffer, 16);
	return fputsn(fd, buffer, count);
}


/* taken from naiveConsole :) */
static int print_to_base(int value, char * buffer, int base)
{
	char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	//Calculate characters for each digit
	do
	{
		int remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}