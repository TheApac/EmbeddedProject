//
// Created by acuevas on 25/02/19.
//

#include "hex2dec.h"
#include <string.h>

unsigned int hex2dec(char hexVal[]) {
	int len = strlen(hexVal);
	int base = 1;
	unsigned int dec_val = 0;
	// Iterate over each character, starting at the end (do not read first to chars as its "0x")
	for (int i = len - 1; i >= 2; i--) {
		// If the value is a number
		if (hexVal[i] >= '0' && hexVal[i] <= '9') {
			// Convert the ascii value to a decimal value and multiply by the base and add to total
			dec_val += (hexVal[i] - 48) * base;
			// Multiply the base by 16 to read the next byte
			base = base * 16;
			// If the value is a capital letter
		} else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
			// Convert the ascii value to a decimal value and multiply by the base and add to total
			dec_val += (hexVal[i] - 55) * base;
			// Multiply the base by 16 to read the next byte
			base = base * 16;
		}
	}
	// Return the total value
	return dec_val;
}