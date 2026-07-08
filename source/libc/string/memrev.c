#include <string.h>

void* memrev(void* base, size_t size, size_t element_size) {
	unsigned char* start = (unsigned char *)base;
	unsigned char* end = start + (size - 1) * element_size;

	unsigned char buffer[element_size];

	while(start < end) {
		memcpy(buffer, start, element_size);
		memcpy(start, end, element_size);
		memcpy(end, buffer, element_size);

		start += element_size;
		end -= element_size;
	}

	return base;
}