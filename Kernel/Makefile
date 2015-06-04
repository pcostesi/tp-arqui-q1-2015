include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
LOADERSRC=loader.asm
INTERRUPTSSRC=i64int.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
INTERRUPTS=$(INTERRUPTSSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(INTERRUPTS) $(OBJECTS) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(INTERRUPTS) $(OBJECTS) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

$(INTERRUPTS):
	$(ASM) $(ASMFLAGS) $(INTERRUPTSSRC) -o $(INTERRUPTS)

clean:
	rm -rf *.o *.bin

.PHONY: all clean
