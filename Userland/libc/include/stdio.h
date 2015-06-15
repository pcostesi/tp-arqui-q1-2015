#ifndef __STD_IO
#define __STD_IO 1

#define STDIN 	0
#define STDOUT 	1
#define STDERR 	2
#define STDRAW 	3
#define SCANF_MAX_STR_BUFFER 64
#include <stdarg.h>

/* The freestanding headers are: <float.h>, <iso646.h>, <limits.h>, <stdalign.h>,
		<stdarg.h>, <stdbool.h>, <stddef.h>, <stdint.h>, and <stdnoreturn.h>.
*/

void putc(char c);
void fputc(int fd, char c);

int puts(char *);
int fputs(int fd, char *);
int fputsn(int fd, char *, int n);

int vfprintf(int fd, char * fmt, va_list ap);
int fprintf(int fd, char *fmt, ...);
int printf(char *fmt, ...);


int fgetc(int fd);
int getc(void);
int fgetsn(int fd, char * c, int n);
int fgets(int fd, char * c, unsigned int n);
int gets(char * c, unsigned int n);

void fungetc(int fd, char c);
void ungetc(char c);

int scanf(char *fmt, ...);
int fscanf(int fd, char *fmt, ...);
int vfscanf(int fd, char *fmt, va_list ap);

#endif