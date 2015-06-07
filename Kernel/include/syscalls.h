#ifndef __syscalls
#define __syscalls 1

#include <interrupts.h>
#include <stdint.h>


int syscall_write(unsigned int fd, char *str, unsigned int size);
int syscall_read(unsigned int fd, char * buf, unsigned int size);
void syscall_pause(void);
void syscall_wake(void);

uint64_t int80h(uint64_t
 sysno, uint64_t
 RDI, uint64_t
 RSI, uint64_t
 RDX, uint64_t
 RCX, uint64_t
 R8, uint64_t
 R9);


#endif