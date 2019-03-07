//
// Created by acuevas on 11/02/19.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "failure.h"
#include "readComponentFromValue.h"
#include "readTypePlaneFromValue.h"
#include "readCountryFromPlaneCode.h"
#include "readFailureFromValue.h"
#include "getFormattedDate.h"

/*
 * Append a clear error log in the failure log file
 * @param failure The failure struct with every important information
 * @param pl The plane on which the error happened
 */


void printFailureToFile(struct failure fail, struct plane pl) {
	FILE *file;
	// Gets the date of the error
	char *timeFile = getFormattedDate(fail.datetime_failure_x, 1);
	char *time = getFormattedDate(fail.datetime_failure_x, 0);
	char *path = (char *) malloc(20);
	// Create the name of the file
	strcpy(path, "Extraction_report_");
	// Increase the number of failures by 1
	nbFailure += 1;
	// Append plane id to name of file
	strcat(path, (char *) pl.id_plane);
	strcat(path, "_");
	strcat(path, time);
	strcat(path, ".txt");

	// If file doesn't exist
	if (fopen(path, "r") == NULL) {
		// First create it
		file = fopen(path, "w");
		// And add header to it
		fprintf(file, "FAILURE REPORT\n\n");
		fprintf(file, "%s\n", pl.id_plane);
		fprintf(file, "%s\n", readTypePlaneFromValue(pl.type_plane));
		fprintf(file, "PLANE NATIONALITY: %s\n", readCountryFromPlaneCode(pl.id_plane));
	} else {
		file = fopen(path, "a");
	}
	if (file == NULL) {
		perror("Error opening file.");
	} else {
		// Append a new failure in the log file
		fprintf(file, "----------\n");
		fprintf(file, "FAILURE %d: %s\n", nbFailure, readFailureFromValue(fail.id_failure_x));
		fprintf(file, "TIME: %s\n", timeFile);
		fprintf(file, "COMPONENT FAILURE: %s\n", readComponentFromValue(fail.id_component_failure_x));
		fprintf(file, "LEVEL CRITICITY: %d\n", fail.level_criticity_failure_x);
		fprintf(file, "COMMENT: %s\n", fail.comment_failure_x);
	}
	// Cleanup
	free(time);
	free(timeFile);
	// Close the file
	fclose(file);
}

