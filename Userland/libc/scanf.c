#include <stdio.h>
#include <stdarg.h>

//int scanf(char *fmt, ...);
//int fscanf(int fd, char *fmt, ...);



int vfscanf(int fd, char * fmt, va_list ap)
{
	int c;
	int buf;
	char * ptr = fmt;
	int in_fmt = 0;
	int read = 0;

	while ((c = *ptr++) != (char) 0) {
			switch (in_fmt) {
				case '%':
				read += 0;//print_number(fd, ap, c);
				break;

				case '\\':
				read += 0;//print_escape(fd, c);
				break;

				case 'x':
				read += 0;//print_escape(fd, c);
				break;

				case 'd':
				read += 0;//print_escape(fd, c);
				break;

				case 'o':
				read += 0;//print_escape(fd, c);
				break;

				case 'n':
				do {
					buf = fgetc(fd);
				} while (buf != '\n' && buf != -1);
				break;

				default:
				in_fmt = 0;
				c = -1;
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