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
	// Try to open the xlsx file
	if ((xlsxioread = xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx")) == NULL) {
		return "noFile";
	}
	char *country;
	char *val;
	xlsxioreadersheet sheet;
	// If file exists, open the right sheet
	const char *sheetname = "ID_PLANES";
	if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
		// If the sheet has been found, iterate over each row
		int line = 0;
		while (xlsxioread_sheet_next_row(sheet)) {
			if (line == 0) {
				// Do not read the first line
				line++;
				continue;
			}
			int col = 0;
			while ((val = xlsxioread_sheet_next_cell(sheet)) != NULL) {
				if (strcmp(val, "") == 0) {
					// Do not read empty cells
					continue;
				}
				if (col == 0) {
					// save the country value for this line
					country = val;
				}
				if (col == 2) {
					// Gets the min value
					char *stringMin = strtok(val, " ");
					if (stringMin == NULL) {
						// If we reach the end of the table
						return "";
					}
					char *stringMax = strtok(NULL, " ");
					// If there is no max value and value equals the one we look for
					if (strcmp("to", stringMax) != 0 && strcmp((char *) code, stringMin) == 0) {
						return country;
					}
					// Retrieves the max value
					stringMax = strtok(NULL, " ");
					//If the value is within the bounds
					if (strcmp((char *) code, stringMin) >= 0 &&
					    strcmp((char *) code, stringMax) <= 0) {
						// ---- Cleanup ----
						xlsxioread_sheet_close(sheet);
						xlsxioread_close(xlsxioread);
						free(val);
						//------------------
						return country;
					}
				}
				col++;
			}
		}
		// If the value couldn't be found, stop the reading process
		xlsxioread_sheet_close(sheet);
	}
	// Close the xlsx file
	xlsxioread_close(xlsxioread);
	// And return an empty string
	return "";
}