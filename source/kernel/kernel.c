#include <stdint.h>
#include <stdio.h>

#include <kernel/drivers/l_vga.h>
#include <kernel/l_tty.h>

#include <kernel/drivers/l_pic.h>

#include <kernel/INT/IDT.h>

void kmain(uint32_t magic, uint32_t mbi_pointer) {
	terminal_init();

	////////////////INTERRUPTS//////////////////
	idt_init();

	pic_remap(0x20, 0x28);
	for (uint8_t i = 0; i < 16; i++) {
    		IRQ_set_mask(i);
	}
	sti();
	////////////////////////////////////////////
}