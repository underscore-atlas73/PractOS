#include <stdint.h>
#include <stdio.h>
#include <kernel/INT/interrupts.h>

char* E_NAMES[] = {
	"E_DIVZERO",
	"E_DEBUG",
	"NMI",
	"BREAK",
	"E_OVERFLOW",
	"E_BOUNDS",
	"E_INVOP",
	"E_DEVNOTAVAIL",
	"E_DOUBLE",
	"E_COPROCSEGOVERRUN",
	"E_INVTSS",
	"E_SEGNOTPRES",
	"E_STACKSEGFAULT",
	"E_GPF",
	"E_PAGEFAULT",
	"RESERVED",
	"E_X87FPE",
	"E_ALIGNCHECK",
	"E_MACHCHECK",
	"E_SIMDFPE",
	"E_VIRT",
	"E_CPE",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"E_HYPINJECT",
	"E_VMMCOMM",
	"E_SECURITY",
	"RESERVED"
};

void master_ISR(struct InterruptState* state) {
	if (state->int_no == 32) {
		PIT_handler(state);
		return;
	}
	if (state->int_no == 33) {
		KB_handler(state);
		return;
	}
	//while(1) {
		printf("EXCEPTION THROWN: %u (%s) WITH CODE %u\nRIP: %p\n", state->int_no, E_NAMES[state->int_no],state->err_code, state->rip);
		//__asm__ volatile ("hlt");
	//}
}
