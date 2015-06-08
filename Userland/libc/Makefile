include ../Makefile.inc

LIB=../libc.a
CSOURCES=$(wildcard *.c)
COBJECTS=$(CSOURCES:.c=.o)
ASMSOURCES=$(wildcard *.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)

all:	clean archive

$(COBJECTS):	$(CSOURCES)

$(ASMOBJECTS):	$(ASMSOURCES)

%.o:	%.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o:	%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

archive:	$(COBJECTS) $(ASMOBJECTS)
	- rm $(LIB)
	ar rcs $(LIB) $(ASMOBJECTS) $(COBJECTS)

clean:
	rm -rf *.o

.PHONY: all clean
