#ifndef IDT_H
#define IDT_H

#include <stdint.h>

static inline void cli(void) {
	__asm__ __volatile__ ("cli");
}

static inline void sti(void) {
	__asm__ __volatile__ ("sti");
}

// A single entry (16 bytes)
struct idt_entry_64 {
    uint16_t offset_low;        // Lower 16 bits of the ISR address
    uint16_t segment_selector;  // Kernel Code Segment selector
    uint8_t  ist;               // Interrupt Stack Table offset (0 for now); THIS WILL BE USED FOR TASKS
    uint8_t  type_attributes;   // Gate type, DPL, and Present flags
    uint16_t offset_mid;        // Middle 16 bits of the ISR address
    uint32_t offset_high;       // Upper 32 bits of the ISR address
    uint32_t reserved;          // Always 0
} __attribute__((packed));

// passed via 'lidt' instruction
struct idtptr_64 {
    uint16_t limit;             // Must be size of the IDT array minus 1
    uint64_t base;              // Memory address of first entry
} __attribute__((packed));

// allocate (i should be fine doing this in a header only included once, no?) WRONG. THINK AGAIN.
extern struct idt_entry_64 idt[256];
extern struct idtptr_64 idtptr;

// populate an entry
void idt_set_gate(uint8_t num, uint64_t isr_address, uint16_t kernel_cs, uint8_t flags);

void idt_init(void);

#endif
