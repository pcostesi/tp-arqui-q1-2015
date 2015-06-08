include ../Makefile.inc

MODULE=sampleCodeModule.bin
MODULE.O=sampleCodeModule.o
SOURCES=$(wildcard *.c)

all: $(MODULE)

$(MODULE.O): $(SOURCES)
	$(GCC) $(GCCFLAGS) -c $(SOURCES) -o $(MODULE.O)

$(MODULE):	$(MODULE.O)
	$(LD) -T sampleCodeModule.ld $(MODULE.O) $(LIBC) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean
