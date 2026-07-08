#ifndef L_TTY_H
#define L_TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <kernel/drivers/l_vga.h>

void terminal_init(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_newline(void);
#define terminal_writestring(str) (terminal_write(str, strlen(str)))

struct TerminalData {
	size_t terminal_row;
	size_t terminal_column;
	uint8_t terminal_color;
	uint16_t* terminal_buffer;
};
extern struct TerminalData terminalData;

#endif