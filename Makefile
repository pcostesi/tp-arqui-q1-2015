all:  clean toolchain bootloader kernel userland image raw

toolchain:
	- cd Toolchain; make all

bootloader:
	cd Bootloader; make all

kernel:
	cd Kernel; make all

userland:
	cd Userland; make all

image: kernel bootloader userland toolchain
	cd Image; make all

run:	image
	bash run.sh

raw:	image
	bash run.sh img

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Userland; make clean
	cd Kernel; make clean

.PHONY: clean bootloader image collections kernel userland all toolchain
