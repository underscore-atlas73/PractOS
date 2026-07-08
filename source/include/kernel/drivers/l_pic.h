#ifndef L_PIC_H
#define L_PIC_H

#define PIC1_COMMAND 0x20  // Master PIC command port
#define PIC1_DATA    0x21  // Master PIC data port
#define PIC2_COMMAND 0xA0  // Slave PIC command port
#define PIC2_DATA    0xA1  // Slave PIC data port

#define ICW1_INIT    0x10  // Initialization command
#define ICW1_ICW4    0x01  // Indicates that ICW4 will be present
#define ICW4_8086    0x01  // 8086/88 (x86) mode

#define PIC_EOI 0x20

void PIC_set_mask(uint8_t);
void PIC_clear_mask(uint8_t);
void PIC_remap(int offset1, int offset2);
void PIC_send_eoi(uint8_t irq);

#endif