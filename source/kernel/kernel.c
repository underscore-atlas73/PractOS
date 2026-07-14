#include <stdint.h>
#include <stdio.h>

#include <kernel/drivers/l_vga.h>
#include <kernel/l_tty.h>

#include <kernel/drivers/l_pic.h>
#include <kernel/drivers/pit.h>
#include <kernel/drivers/l_kb.h>

#include <kernel/INT/IDT.h>

#include <PURACS/chrono.h>

void kmain(uint32_t magic, uint32_t mbi_pointer) {
	terminal_init();

	//printf("%u\n", sysclock);

	////////////////INTERRUPTS//////////////////
	idt_init();

	PIC_remap(0x20, 0x28);
	for (uint8_t i = 0; i < 16; i++) {
    		PIC_set_mask(i);
	}

	pit_init(1000);
	PIC_clear_mask(PIC_PIT);
	PIC_clear_mask(PIC_KB);
	sti();
	////////////////////////////////////////////
	//__asm__ __volatile__ ("int $22");
	//printf("%u\n", sysclock);

	//ksleep(5000);
	//printf("5 second wait");

	while(1) {
		ksleep(100);
		terminalData.terminal_row = 0;
		printf(
		       "CTRL: %i; SHIFT: %i; ALT: %i; SUPER: %i; F1: %i\n",
		       KeyState.ctrl, KeyState.shift, KeyState.alt, KeyState.super, KeyState.F1
		       );
	}

}
