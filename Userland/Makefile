include Makefile.inc

all:	clean libc shell sampleCodeModule sampleDataModule

libc:
	@cd libc; make
	@echo "LibC built"

sampleCodeModule:
	@cd SampleCodeModule; make
	@echo "Sample Code Module built"

shell:
	@cd shell; make
	@echo "Shell built"

sampleDataModule:
	@printf "This is sample data." >> 50-SampleDataModule.bin && dd if=/dev/zero bs=1 count=1 >> SampleDataModule.bin
	@echo "Sample Data Module built"

clean:
	@cd SampleCodeModule; make clean
	@cd shell; make clean
	@cd libc; make clean
	- rm -rf *.bin


.PHONY: clean all libc shell sampleCodeModule sampleDataModule