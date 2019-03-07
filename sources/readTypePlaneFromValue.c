//
// Created by acuevas on 11/02/19.
//

#include "readTypePlaneFromValue.h"
#include <xlsxio_read.h>
#include "stdlib.h"
#include "hex2dec.h"

char *readTypePlaneFromValue(unsigned int value) {
	xlsxioreader xlsxioread;
	// Try to open the xlsx file
	if ((xlsxioread = xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx")) == NULL) {
		return "noFile";
	}
	char *type;
	char *val;
	xlsxioreadersheet sheet;
	// If file exists, open the right sheet
	const char *sheetname = "TYPE_PLANE";
	if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
		// If the sheet has been found, iterate over each row
		while (xlsxioread_sheet_next_row(sheet)) {
			int col = 0;
			// Read each cell of the row
			while ((val = xlsxioread_sheet_next_cell(sheet)) != NULL) {
				// If the value is the one we are looking for
				if (col == 1 && hex2dec(val) == value) {
					// Return the type associated to the value
					type = xlsxioread_sheet_next_cell(sheet);
					// ---- Cleanup ----
					free(val);
					xlsxioread_sheet_close(sheet);
					xlsxioread_close(xlsxioread);
					//------------------
					return type;
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