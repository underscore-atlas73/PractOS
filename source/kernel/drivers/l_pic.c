#include <kernel/io.h>
#include <kernel/drivers/l_pic.h>

void PIC_set_mask(uint8_t IRQline) {
	uint16_t port;
	uint8_t value;

	if (IRQline < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQline -= 8;
	}

	// Read current mask
	value = inb(port);

	// Set bit to 1 to MASK interrupt
	value |= (1 << IRQline);

	// Write new mask back
	outb(port, value);
}

void PIC_clear_mask(uint8_t IRQline) {
	uint16_t port;
	uint8_t value;

	if (IRQline < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQline -= 8;
	}

	// Read current mask
	value = inb(port);

	// Set bit to 0 to UNMASK interrupt
	value &= ~(1 << IRQline);

	// Write new mask back
	outb(port, value);
}

void PIC_remap(int offset1, int offset2) {
	uint8_t a1, a2;

	// Save interrupt masks
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	// Start initialization sequence (cascade mode)
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	// Set vector offsets
	outb(PIC1_DATA, offset1); // Master PIC vector offset (0x20)
	io_wait();
	outb(PIC2_DATA, offset2); // Slave PIC vector offset (0x28)
	io_wait();

	// Tell Master there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC1_DATA, 4);
	io_wait();
	// Tell Slave its identity (0000 0010)
	outb(PIC2_DATA, 2);
	io_wait();

	// Set x86 mode
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Restore saved masks
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void PIC_send_eoi(uint8_t irq) {
	if (irq >= 8) {
		// If interrupt came from Slave PIC, we must tell both!
		outb(PIC2_COMMAND, PIC_EOI);
	}
	// Always tell Master PIC
	outb(PIC1_COMMAND, PIC_EOI);
}