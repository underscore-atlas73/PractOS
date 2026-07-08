#include <kernel/INT/IDT.h>

struct idt_entry_64 idt[256];
struct idtptr_64 idtptr;

void idt_set_gate(uint8_t num, uint64_t isr_address, uint16_t kernel_cs, uint8_t flags) {
    idt[num].offset_low      = (uint16_t)(isr_address & 0xFFFF);
    idt[num].segment_selector= kernel_cs; // literally the only code segment in the gdt
    idt[num].ist             = 0;
    idt[num].type_attributes = flags; // 10001110 should be default in kernel; present (1), ring 0 (00), 64 bit int gate (01110)
    idt[num].offset_mid      = (uint16_t)((isr_address >> 16) & 0xFFFF);
    idt[num].offset_high     = (uint32_t)((isr_address >> 32) & 0xFFFFFFFF);
    idt[num].reserved        = 0;
}

extern void eISR0();
extern void eISR1();
extern void eISR2();
extern void eISR3();
extern void eISR4();
extern void eISR5();
extern void eISR6();
extern void eISR7();
extern void eISR8();
extern void eISR9();
extern void eISR10();
extern void eISR11();
extern void eISR12();
extern void eISR13();
extern void eISR14();
extern void eISR15();
extern void eISR16();
extern void eISR17();
extern void eISR18();
extern void eISR19();
extern void eISR20();
extern void eISR21();
extern void eISR22();
extern void eISR23();
extern void eISR24();
extern void eISR25();
extern void eISR26();
extern void eISR27();
extern void eISR28();
extern void eISR29();
extern void eISR30();
extern void eISR31();

extern void load_idt(uint64_t idtptr_addr);
extern uint8_t __KERNEL_GDT;

void idt_init(void) {
	idtptr.limit = (sizeof(struct idt_entry_64) * 256) - 1;
	idtptr.base  = (uint64_t)&idt;

	for (uint16_t i = 0; i < 256; i++) {
		idt_set_gate(i, 0, 0, 0);
	}

	idt_set_gate(0, (uint64_t)eISR0, __KERNEL_GDT, 0x8E);
	idt_set_gate(1, (uint64_t)eISR1, __KERNEL_GDT, 0x8E);
	idt_set_gate(2, (uint64_t)eISR2, __KERNEL_GDT, 0x8E);
	idt_set_gate(3, (uint64_t)eISR3, __KERNEL_GDT, 0x8E);
	idt_set_gate(4, (uint64_t)eISR4, __KERNEL_GDT, 0x8E);
	idt_set_gate(5, (uint64_t)eISR5, __KERNEL_GDT, 0x8E);
	idt_set_gate(6, (uint64_t)eISR6, __KERNEL_GDT, 0x8E);
	idt_set_gate(7, (uint64_t)eISR7, __KERNEL_GDT, 0x8E);
	idt_set_gate(8, (uint64_t)eISR8, __KERNEL_GDT, 0x8E);
	idt_set_gate(9, (uint64_t)eISR9, __KERNEL_GDT, 0x8E);
	idt_set_gate(10, (uint64_t)eISR10, __KERNEL_GDT, 0x8E);
	idt_set_gate(11, (uint64_t)eISR11, __KERNEL_GDT, 0x8E);
	idt_set_gate(12, (uint64_t)eISR12, __KERNEL_GDT, 0x8E);
	idt_set_gate(13, (uint64_t)eISR13, __KERNEL_GDT, 0x8E);
	idt_set_gate(14, (uint64_t)eISR14, __KERNEL_GDT, 0x8E);
	idt_set_gate(15, (uint64_t)eISR15, __KERNEL_GDT, 0x8E);
	idt_set_gate(16, (uint64_t)eISR16, __KERNEL_GDT, 0x8E);
	idt_set_gate(17, (uint64_t)eISR17, __KERNEL_GDT, 0x8E);
	idt_set_gate(18, (uint64_t)eISR18, __KERNEL_GDT, 0x8E);
	idt_set_gate(19, (uint64_t)eISR19, __KERNEL_GDT, 0x8E);
	idt_set_gate(20, (uint64_t)eISR20, __KERNEL_GDT, 0x8E);
	idt_set_gate(21, (uint64_t)eISR21, __KERNEL_GDT, 0x8E);
	idt_set_gate(22, (uint64_t)eISR22, __KERNEL_GDT, 0x8E);
	idt_set_gate(23, (uint64_t)eISR23, __KERNEL_GDT, 0x8E);
	idt_set_gate(24, (uint64_t)eISR24, __KERNEL_GDT, 0x8E);
	idt_set_gate(25, (uint64_t)eISR25, __KERNEL_GDT, 0x8E);
	idt_set_gate(26, (uint64_t)eISR26, __KERNEL_GDT, 0x8E);
	idt_set_gate(27, (uint64_t)eISR27, __KERNEL_GDT, 0x8E);
	idt_set_gate(28, (uint64_t)eISR28, __KERNEL_GDT, 0x8E);
	idt_set_gate(29, (uint64_t)eISR29, __KERNEL_GDT, 0x8E);
	idt_set_gate(30, (uint64_t)eISR30, __KERNEL_GDT, 0x8E);
	idt_set_gate(31, (uint64_t)eISR31, __KERNEL_GDT, 0x8E);

	load_idt((uint64_t)&idtptr);
}