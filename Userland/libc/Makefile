include ../Makefile.inc

MODULE=../libc.o
LIB=../libc.a
CSOURCES=$(wildcard *.c)
COBJECTS=$(CSOURCES:.c=.o)
ASMSOURCES=$(wildcard *.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)

all:	archive

$(COBJECTS):	$(CSOURCES)

$(ASMOBJECTS):	$(ASMSOURCES)

%.o:	%.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o:	%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

archive:	$(COBJECTS) $(ASMOBJECTS)
	ar rcs $(LIB) $(COBJECTS) $(ASMOBJECTS)
	ld -r $(COBJECTS) $(ASMOBJECTS) -o $(MODULE)

clean:
	- rm -rf *.o *.co *.ao *.a

.PHONY: all clean
