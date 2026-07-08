#include <kernel/l_tty.h>

struct TerminalData terminalData;

void terminal_init(void) {
	terminalData.terminal_row = 0;
	terminalData.terminal_column = 0;
	terminalData.terminal_color = 0x07;
	terminalData.terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminalData.terminal_buffer[y * VGA_WIDTH + x] = vga_entry(' ', terminalData.terminal_color);
		}
	}
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	terminalData.terminal_buffer[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	terminal_putentryat(c, terminalData.terminal_color, terminalData.terminal_column, terminalData.terminal_row);
	if (++terminalData.terminal_column == VGA_WIDTH)
		terminal_newline();
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++) 
		terminal_putchar(data[i]);
}

void terminal_newline(void) {
	terminalData.terminal_column = 0;
	if (++terminalData.terminal_row == VGA_HEIGHT) {
		terminalData.terminal_row = 0;
		//TODO: Implement scrolling + buffering. We have enough room between 0xB8000 and 0xBFFFF for 8 screens
	}
}