//
// Created by acuevas on 25/02/19.
//

#include "hex2dec.h"
#include <string.h>

unsigned int hex2dec(char hexVal[])
{
	int len = strlen(hexVal);
	int base = 1;
	unsigned int dec_val = 0;

	for (int i=len-1; i>=2; i--) {
		if (hexVal[i]>='0' && hexVal[i]<='9') {
			dec_val += (hexVal[i] - 48)*base;
			base = base * 16;
		} else if (hexVal[i]>='A' && hexVal[i]<='F') {
			dec_val += (hexVal[i] - 55)*base;
			base = base*16;
		}
	}
	return dec_val;
}