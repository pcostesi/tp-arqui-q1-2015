GCC=gcc
GPP=g++
LD=ld
AR=ar
ASM=nasm

GCCFLAGS=-m64 -fno-exceptions -std=c99 -Wall -Werror -ffreestanding -nostdlib -fno-common -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc -I../libc/include -I./include
ARFLAGS=rvs
ASMFLAGS=-felf64
LIBC=-L../ -L./ -lc
CRT0=../crt0.o