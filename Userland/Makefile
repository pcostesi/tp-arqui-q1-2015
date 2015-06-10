include Makefile.inc

all:	clean libc shell

libc:
	@cd libc; make
	@echo "LibC built"

shell:
	@cd shell; make
	@echo "Shell built"

clean:
	@cd shell; make clean
	@cd libc; make clean
	- rm -rf *.bin


.PHONY: clean all libc shell