#ifndef __syscalls
#define __syscalls 1

#include <interrupts.h>


void syscall_write(unsigned int fd, char *str, unsigned int size);
int syscall_read(unsigned int fd, char * buf, unsigned int size);
void syscall_pause(void);
void syscall_wake(void);

IntSysHandler int80h(int sysno, int RDI, int RSI, int RDX, int RCX, int R8, int R9);


#endif