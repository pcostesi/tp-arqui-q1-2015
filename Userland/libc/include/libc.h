#ifndef __LIBC
#define __LIBC 1

/* syscalls */
extern int write(unsigned int fd, char * str, unsigned int size);
extern void pause(void);
extern int read(unsigned int fd, char * str, unsigned int size);
extern void halt(void);
extern void shutdown(void);
extern void towel(void);


#endif