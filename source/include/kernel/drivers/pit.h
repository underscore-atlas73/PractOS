#ifndef PIT_H
#define PIT_H

#include <stdint.h>
#include <kernel/io.h>
#include <kernel/drivers/l_pic.h>

#define PIT_COMMAND 	0x43 //WRITE ONLY!!
#define PIT_CH0_DATA	0x40 //rw
//#define PIT_CH1_DATA	0x41 //deprecated; used for dram refresh in the ancient days
//#define PIT_CH2_DATA	0x42 //pc speaker

#define PIT_INIT	0b00110110 	//00: channel 0 (IRQ0) (channel 0x11 is for 8254 read-back?);
					//11: low-byte then high-byte;
					//011: mode 3 (square wave)
					//	0 0 0 = Mode 0 (interrupt on terminal count)
                			//	0 0 1 = Mode 1 (hardware re-triggerable one-shot)
                			//	0 1 0 = Mode 2 (rate generator)
                			//	0 1 1 = Mode 3 (square wave generator)
                			//	1 0 0 = Mode 4 (software triggered strobe)
                			//	1 0 1 = Mode 5 (hardware triggered strobe)
                			//	1 1 0 = Mode 2 (rate generator, same as 010b)
                			//	1 1 1 = Mode 3 (square wave generator, same as 011b)
					//0: NOT BCD (16 bit binary)
#define PIT_FREQ	1193182

void pit_init(uint32_t frequency);

struct InterruptState;
void PIT_handler(struct InterruptState *state);

extern volatile uint64_t sysclock;

#endif
