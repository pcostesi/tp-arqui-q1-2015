include ../Makefile.inc

LIB=../libc.a
CSOURCES=$(wildcard *.c)
COBJECTS=$(CSOURCES:.c=.o)
ASMSOURCES=syscalls.asm
ASMOBJECTS=$(ASMSOURCES:.asm=.o)

all:	clean $(CRT0) $(LIB)

$(COBJECTS):	$(CSOURCES)

$(ASMOBJECTS):	$(ASMSOURCES)

$(CRT0):	crt0.asm
	$(ASM) $(ASMFLAGS) crt0.asm -o $(CRT0)

%.o:	%.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o:	%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LIB):	$(COBJECTS) $(ASMOBJECTS) $(CRT0)
	ar rcs $(LIB) $(ASMOBJECTS) $(COBJECTS)

clean:
	rm -rf *.o

.PHONY: all clean
