all:  toolchain bootloader kernel userland image

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

run:	clean image
	bash run.sh

raw:	clean image
	bash run.sh img

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Kernel; make clean
	cd Userland; make clean

.PHONY: bootloader image collections kernel userland all clean toolchain
