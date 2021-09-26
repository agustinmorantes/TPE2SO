
all: shared bootloader kernel userland image

shared: 
	cd Shared; make all

bootloader:
	cd Bootloader; make all

kernel:
	cd Kernel; make all

userland:
	cd Userland; make all

image: shared kernel bootloader userland
	cd Image; make all

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Kernel; make clean
	cd Userland; make clean
	cd Shared; make clean

.PHONY: bootloader image collections kernel userland all clean shared
