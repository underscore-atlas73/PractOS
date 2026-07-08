#include <string.h>

char* itoa(int num, char* str, unsigned int base, bool isSigned)
{
	int i = 0;
	bool isNegative = false;

	// Handle 0 explicitly
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	if (num < 0 && isSigned) {
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num = num / base;
	}

	// If number is negative, append '-'
	if (base == 2) {
		str[i++] = 'b';
		str[i++] = '0';
	}

	if (base == 8) {
		str[i++] = 'o';
		str[i++] = '0';
	}

	if (base == 16) {
		str[i++] = 'x';
		str[i++] = '0';
	}

	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	memrev(str, i, sizeof(char));

	return str;
}