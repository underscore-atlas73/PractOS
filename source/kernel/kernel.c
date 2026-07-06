#include <stdint.h>

void kmain(uint32_t magic, uint32_t mbi_pointer) {
	volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;

	const char* str = "Successfully entered 64-bit Long Mode natively via Multiboot2!";
	const char* failStr = "Invalid Multiboot2 Magic recieved! Bailing out...";

	if (magic != 0x36D76289) {
		for (int i = 0; failStr[i] != '\0'; i++) {
			// High byte: Color attribute (0x0F = White text on Black background)
			// Low byte: Character ASCII code
			vga_buffer[i] = (uint16_t)failStr[i] | (0x07 << 8);
		}
		return;
	}


	for (int i = 0; str[i] != '\0'; i++) {
		// High byte: Color attribute (0x0F = White text on Black background)
		// Low byte: Character ASCII code
		vga_buffer[i] = (uint16_t)str[i] | (0x07 << 8);
	}
}