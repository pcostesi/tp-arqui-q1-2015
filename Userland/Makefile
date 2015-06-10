include Makefile.inc

all:	clean libc shell tpl

libc:
	@cd libc; make
	@echo "LibC built"

shell:	libc
	@cd shell; make
	@echo "Shell built"


tpl:	libc
	@cd tpl; make
	@echo tpl built

clean:
	@cd shell; make clean
	@cd libc; make clean
	- rm -rf *.bin


.PHONY: clean all libc shell