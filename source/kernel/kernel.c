#include <stdint.h>
#include <stdio.h>

#include <kernel/drivers/l_vga.h>
#include <kernel/l_tty.h>

#include <kernel/drivers/l_pic.h>
#include <kernel/drivers/pit.h>

#include <kernel/INT/IDT.h>

void kmain(uint32_t magic, uint32_t mbi_pointer) {
	terminal_init();

	////////////////INTERRUPTS//////////////////
	idt_init();

	PIC_remap(0x20, 0x28);
	for (uint8_t i = 0; i < 16; i++) {
    		PIC_set_mask(i);
	}

	pit_init(1000);
	PIC_clear_mask(0);
	sti();

	//__asm__ __volatile__ ("int $22");

	while(1){}
	////////////////////////////////////////////
}