//
// Created by acuevas on 11/02/19.
//

#include "readComponentFromValue.h"
#include "stdlib.h"
#include <xlsxio_read.h>
#include "hex2dec.h"

char *readComponentFromValue(unsigned int value) {
	xlsxioreader xlsxioread;
	// Try to open the xlsx file
	if ((xlsxioread = xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx")) == NULL) {
		return "noFile";
	}
	char *type;
	char *val;
	xlsxioreadersheet sheet;
	// If file exists, open the right sheet
	const char *sheetname = "ID_COMPONENT_FAILURE_X";
	if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
		// If the sheet has been found, iterate over each row
		while (xlsxioread_sheet_next_row(sheet)) {
			int col = 0;
			while ((val = xlsxioread_sheet_next_cell(sheet)) != NULL) {
				// If the value is the one we are looking for
				if (col == 1 && hex2dec(val) == value) {
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
	xlsxioread_close(xlsxioread);
	return "";
}
