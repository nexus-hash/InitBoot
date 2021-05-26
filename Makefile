all:
	nasm -f elf32 -g -F dwarf kernel.asm -o kernel.o
	nasm -f elf32 -g -F dwarf lowlevel.asm -o lowlevel.o
	i686-elf-gcc -g -m32  -c main.c -o main.o -ffreestanding -O3 -Wall -Wextra -pedantic
	i686-elf-gcc -g -m32  -c keyb.c -o keyb.o -ffreestanding -O3 -Wall -Wextra -pedantic
	i686-elf-gcc -g -m32  -Wl,--build-id=none -T link.ld -o kernel.elf -ffreestanding -nostdlib lowlevel.o main.o keyb.o kernel.o -lgcc

clean:
	rm *.o kernel.elf