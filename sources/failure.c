//
// Created by acuevas on 11/02/19.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "failure.h"

/*
 * Append a clear error log in the failure log file
 * @param failure The failure struct with every important information
 */


void printFailureToFile(struct failure fail) {
	FILE *file;
	time_t     timeDate;
	struct tm  ts;
	char       buf[80];

	nbFailure += 1;
	file = fopen("error.log", "a");
	if(file == NULL) {
		perror("Error opening file.");
	} else {
		fprintf(file, "----------\n");
		fprintf(file, "FAILURE %d: %d\n", nbFailure, fail.id_failure_x);
		timeDate = fail.datetime_failure_x;
		ts = *localtime(&timeDate);
		strftime(buf, sizeof(buf), "%Y/%m/%d-%H:%M:%S", &ts);
		fprintf(file, "TIME: %s\n", buf);
		fprintf(file, "COMPONENT FAILURE: %d\n", fail.id_component_failure_x);
		fprintf(file, "LEVEL CRITICITY: %d\n", fail.level_criticity_failure_x);
		fprintf(file, "COMMENT: %s\n", fail.comment_failure_x);
	}
	fclose(file);
}

