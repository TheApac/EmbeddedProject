//
// Created by acuevas on 11/02/19.
//

#include "../include/readCountryFromPlaneCode.h"

char* readCountryFromPlaneCode(unsigned char code[]) {
	xlsxioreader xlsxioread;
	if ((xlsxioread = xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx")) == NULL) {
		return "";
	}
	char* country;
	xlsxioreadersheet sheet;
	const char* sheetname = "ID_PLANES";
	if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
		while (xlsxioread_sheet_next_row(sheet)) {
			int col = 0;
			while ((val = xlsxioread_sheet_next_cell(sheet)) != NULL) {
				if (col == 0) {
					country = val;
				}
				if (col == 1 && val == code) {
					free(val);
					xlsxioread_sheet_close(sheet);
					xlsxioread_close(xlsxioread);
					return country;
				}
				col++;
			}
		}
		xlsxioread_sheet_close(sheet);
	}
	xlsxioread_close(xlsxioread);
	return "";
}