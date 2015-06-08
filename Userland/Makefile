include Makefile.inc

all: libc sampleCodeModule sampleDataModule

libc:
	cd libc; make

sampleCodeModule:	libc
	cd SampleCodeModule; make

sampleDataModule:
	printf "This is sample data." >> SampleDataModule.bin && dd if=/dev/zero bs=1 count=1 >> SampleDataModule.bin

clean:
	cd SampleCodeModule; make clean
	cd libc; make clean
	rm -rf *.bin


.PHONY: libc sampleCodeModule all clean
