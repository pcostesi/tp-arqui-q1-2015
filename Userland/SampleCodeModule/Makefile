include ../Makefile.inc

MODULE=sampleCodeModule.bin
MODULE.O=sampleCodeModule.o
SOURCES=$(wildcard *.c)

all: stdlib $(MODULE)

stdlib:
	cd ../libc; make

$(MODULE.O): $(SOURCES)
	$(GCC) $(GCCFLAGS) -c $(SOURCES) -o $(MODULE.O)

$(MODULE):	$(MODULE.O)
	$(LD) -T sampleCodeModule.ld $(MODULE.O) -lc -L.. -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean
