all:  clean toolchain bootloader kernel userland image raw

deps:
	sudo apt-get install -q nasm qemu=2.0.0+dfsg-2ubuntu1.12 gcc make

toolchain:
	- cd Toolchain; make all

bootloader:
	cd Bootloader; make all

kernel:	bootloader
	cd Kernel; make all

userland:	kernel toolchain
	cd Userland; make all

image: clean kernel bootloader userland
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
