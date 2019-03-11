//
// Created by acuevas on 11/02/19.
//
#include <time.h>
#include "getFormattedDate.h"
#include <stdio.h>
#include <stdlib.h>

char *getFormattedDate(unsigned int dateTime, int insideFile) {
	long int sec = dateTime;
	// Convert the seconds to a timestamp
	time_t time = sec;
	// Convert the timestamp to a date struct at the localtime
	struct tm *tmDate = localtime(&time);
	char buf[200];// = malloc(sizeof(char) * 80);
	// Convert the date to a formatted string
	if (insideFile == 0) {
		strftime(buf, 20, "%Y_%m_%d_%H_%M_%S", tmDate);
	} else {
		strftime(buf, 20, "%Y/%m/%d-%H:%M:%S", tmDate);
	}
	char *ret;
	ret = buf;
	return ret;
}
