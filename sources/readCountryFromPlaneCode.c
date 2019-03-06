//
// Created by acuevas on 11/02/19.
//

#include "readCountryFromPlaneCode.h"
#include <xlsxio_read.h>
#include "stdlib.h"
#include <string.h>
#include <stdio.h>

char *readCountryFromPlaneCode(unsigned char code[]) {
	xlsxioreader xlsxioread;
	if ((xlsxioread = xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx")) == NULL) {
		return "noFile";
	}
	char *country;
	char *val;
	xlsxioreadersheet sheet;
	const char *sheetname = "ID_PLANES";
	if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
		int line = 0;
		while (xlsxioread_sheet_next_row(sheet)) {
			if (line == 0) {
				line++;
				continue;
			}
			int col = 0;
			while ((val = xlsxioread_sheet_next_cell(sheet)) != NULL) {
				if (strcmp(val, "") == 0) {
					continue;
				}
				if (col == 0) {
					country = val;
				}
				if (col == 2) {
					char *stringMin = strtok(val, " ");
					if (stringMin == NULL) {
						return "";
					}
					char *stringMax = strtok(NULL, " ");
					if (strcmp("to", stringMax) != 0 && strcmp((char *) code, stringMin) == 0) {
						return country;
					}
					stringMax = strtok(NULL, " ");
					if (strcmp((char *) code, stringMin) >= 0 &&
					    strcmp((char *) code, stringMax) <= 0) {
						xlsxioread_sheet_close(sheet);
						xlsxioread_close(xlsxioread);
						return country;
					}
				}
				col++;
			}
		}
		xlsxioread_sheet_close(sheet);
	}
	xlsxioread_close(xlsxioread);
	return "";
}