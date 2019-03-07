/**
 * \file randomError.h
 * \author BSU
 * \brief Contain an array of planes id, an array of plane type and a function for random error generation
 */
#ifndef EMBEDDEDPROJECT_RANDOMERROR_H
#define EMBEDDEDPROJECT_RANDOMERROR_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plane.h"
#include "failure.h"

/**
 * \brief an array of plane ids
 */
char *idPlane[61] = {"YA-AAA", "ZA-AAA", "7T-AAA", "C3-AAA", "D2-AAA", "VP-AAA", "V2-AAA", "LV-AAA", "LQ-AAA", "EK-10000", "P4-AAA", "VH-AAA", "OE-AAA", "OE-BAA", "OE-LAA", "OE-VAA", "OE-WAA", "OE-XAA", "OE-0001",
					"OE-9000", "4K-AZ1", "4K-10000", "C6-AAA", "A9C-AA", "S2-AAA", "8P-AAA", "EW-10000", "EW-100AA", "EW-200PA", "EW-100PJ", "EW-001DA", "EW-0001L", "OO-AAA", "OO-RAA", "OO-BAA", "OO-YAA", "OO-01",
					"OO-501", "V3-AAA", "TY-AAA", "VP-BAA", "VQ-BAA", "A5-AAA", "CP-1000", "T9-AAA", "E7-AAA", "A2-AAA", "PP-AAA", "PR-AAA", "PS-AAA", "PT-AAA", "PU-AAA", "VP-LAA", "V8-AAA", "V8-AA1",
					"V8-001", "LZ-AAA", "XT-AAA", "9U-AAA", "XU-AAA", "TJ-AAA"};
/**
 * \brief an array of plane type
 */
char *typePlane[11] = { "320", "330", "350", "380", "400", "295", "737", "747", "767", "777", "787"};


/**
 * \brief Procedure for random error generation
 * \param nb number of errors to be generate
 * \return a formated result with all failure
 */
char *autoGeneration(int nb);

#endif //EMBEDDEDPROJECT_RANDOMERROR_H
