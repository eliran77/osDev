#include "../include/screen.h"
#include "../include/gdt.h"

extern void loadGdt(uint32_t); 

struct gdt_entry 
{
	uint16_t low_limit;
	uint16_t low_base;
	uint8_t middle_base;	
	uint8_t access_byte;
	uint8_t flags_and_high_limit;
	uint8_t high_base;
}__attribute__((packed));
typedef struct gdt_entry gdt_entry;

struct gdtr 
{
	uint16_t size;
	uint32_t base;
}__attribute__((packed));
typedef struct gdtr gdtr;

//global var
gdt_entry entries[5]; // gdt with 5 entries.
gdtr pGdt; // pointer to the gdt table.


gdt_entry creatEntryGdt(uint32_t base, uint32_t limit, uint8_t accessByte, uint8_t flags)
{
	gdt_entry entry;	
	entry.low_limit = (limit & 0xFFFF);
	entry.low_base = (base & 0xFFFF);
	entry.middle_base = (base >> 16) & 0xFF;
	entry.access_byte = accessByte;
	entry.flags_and_high_limit = (limit >> 16) & 0x0F; // set the 4 bit limit.
	entry.flags_and_high_limit |= flags & 0xF0; // set the flags.
	entry.high_base = (base >> 24) & 0xFF;
	
	return entry;  
}

void gdtSetUp()
{
	pGdt.size = sizeof(entries) - 1;
	pGdt.base  = (uint32_t) & entries;
	entries[0] = creatEntryGdt(0, 0, 0, 0);
	entries[1] = creatEntryGdt(0, 0xFFFFFFFF, 0x9A, 0xCF);
	entries[2] = creatEntryGdt(0, 0xFFFFFFFF, 0x92, 0xCF);
	entries[3] = creatEntryGdt(0, 0xFFFFFFFF, 0xFA, 0xCF);
	entries[4] = creatEntryGdt(0, 0xFFFFFFFF, 0xF2, 0xCF);
	loadGdt((uint32_t)&pGdt);
}




