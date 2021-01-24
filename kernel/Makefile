TARGET:=/home/eliran/cross/bin/i686-elf

all:clean kernel.o boot.o 
	$(TARGET)-gcc -T ../resources/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib ../resources/boot.o kernel.o string.o screen.o loadGdt.o gdt.o initIsr.o loadIdt.o isr.o  idt.o -lgcc
	qemu-system-i386 -kernel myos.bin

kernel.o:screen.o loadGdt.o gdt.o initIsr.o loadIdt.o isr.o idt.o 
	$(TARGET)-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: kernel.o
	nasm -f elf -o ../resources/boot.o ../resources/boot.s

string.o:
	$(TARGET)-gcc -c string.c -o string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

screen.o:string.o
	$(TARGET)-gcc -c screen.c -o screen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

loadGdt.o:
	nasm -f elf -o loadGdt.o loadGdt.asm 

gdt.o: loadGdt.o
	$(TARGET)-gcc -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

initIsr.o: 
	nasm -f elf -o initIsr.o initIsr.asm

loadIdt.o:
	nasm -f elf -o loadIdt.o loadIdt.asm

isr.o: 
	$(TARGET)-gcc -c isr.c -o isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra	


idt.o:initIsr.o loadIdt.o isr.o
	$(TARGET)-gcc -c idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra	

clean: 
	$(shell rm -rf *.o myos.bin)

run:	
	qemu-system-i386 -kernel myos.bin



