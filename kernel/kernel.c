#include "../include/screen.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/string.h"

void kmain(void) 
{
	initTerminal();
	printf("%s", "Weclome\n");
	printf("%s", "________________________________________________________________________________\n");
	
	printf("%s", "Init Gdt\n");
	gdtSetUp();
	printf("%s", "Gdt setup\n");

	printf("%s", "Init Idt\n");
	idtSetUp();
	printf("%s", "IDT setup.\n");

	printf("%s", "Sending interrupt.\n");
	__asm__("int $0x08");



    printf("%s", "....");
}
