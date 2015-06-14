#include <stdio.h>
#include <stdarg.h>

static int print_str(int fd, char * str);
static int print_dec(int fd, int n);
static int print_oct(int fd, int n);
static int print_hex(int fd, int n);
static int print_chr(int fd, int c);
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

		case 'c':
		written = print_chr(fd, va_arg(ap, int));
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
                written += print_number(fd, ap, c);
                in_fmt = 0;
            } else if (c == '%') {
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

static int print_chr(int fd, int c)
{
	fputc(fd, (char)(c & 0xFF));
	return 1;
}

static int print_dec(int fd, int n)
{
	int count;
	char buffer[20] = {0};
	count = print_to_base(n, buffer, 10);
	fputsn(fd, buffer, count);
	return count;
}

static int print_oct(int fd, int n)
{
	int count;
	char buffer[20] = {0};
	count = print_to_base(n, buffer, 8);
	fputsn(fd, buffer, count);
	return count;
}

static int print_hex(int fd, int n)
{
	int count;
	char buffer[20] = {0};
	count = print_to_base(n, buffer, 16);
	fputsn(fd, buffer, count);
	return count;
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
		*p++ = remainder + ((remainder < 10) ? '0' : 'A' - 10);
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
