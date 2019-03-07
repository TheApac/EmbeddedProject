//
// Created by acuevas on 11/02/19.
//
#include <time.h>
#include "getFormattedDate.h"
#include <stdio.h>
#include <stdlib.h>

char *getFormattedDate(unsigned int dateTime) {
	long int sec = dateTime;
	// Convert the seconds to a timestamp
	time_t time = sec;
	// Convert the timestamp to a date struct at the localtime
	struct tm *tmDate = localtime(&time);
	char *buf = malloc(sizeof(char) * 80);
	// Convert the date to a formatted string
	strftime(buf, sizeof(buf), "%Y/%m/%d-%H:%M:%S", tmDate);
	return buf;
}
