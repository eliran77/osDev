#include "../include/isr.h"
#include "../include/screen.h"

void isr_handler(registers_t regs)
{
	displayInteger(regs.int_no);

}
