//
// Created by acuevas on 11/02/19.
//

#include "../include/readFailureFromValue.h"

char* readFailureFromValue(unsigned int value) {
	xlsxioreader xlsxioread;
	if ((xlsxioread = xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx")) == NULL) {
		return "";
	}
	char* type;
	xlsxioreadersheet sheet;
	const char* sheetname = "ID_FAILURE_X";
	if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
		while (xlsxioread_sheet_next_row(sheet)) {
			int col = 0;
			while ((val = xlsxioread_sheet_next_cell(sheet)) != NULL) {
				if (col == 1 && val == value) {
					type = xlsxioread_sheet_next_cell(sheet);
					free(val);
					xlsxioread_sheet_close(sheet);
					xlsxioread_close(xlsxioread);
					return type;
				}
				col++;
			}
		}
		xlsxioread_sheet_close(sheet);
	}
	xlsxioread_close(xlsxioread);
	return "";
}