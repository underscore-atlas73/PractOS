#include "kernel/drivers/l_pic.h"
#include <kernel/drivers/pit.h>

volatile uint64_t sysclock = 0;

void pit_init(uint32_t frequency) {
    uint32_t divisor = PIT_FREQ / frequency;

    outb(PIT_COMMAND, PIT_INIT);

    uint8_t low_byte = (uint8_t)(divisor & 0xFF);
    outb(PIT_CH0_DATA, low_byte);

    uint8_t high_byte = (uint8_t)((divisor >> 8) & 0xFF);
    outb(PIT_CH0_DATA, high_byte);
}

void PIT_handler(struct InterruptState *state) {
	sysclock++;
	PIC_send_eoi(PIC_PIT);
}
