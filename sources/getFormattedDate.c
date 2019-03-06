//
// Created by acuevas on 11/02/19.
//
#include <time.h>
#include "getFormattedDate.h"
#include <stdio.h>
#include <stdlib.h>

char *getFormattedDate(unsigned int dateTime) {
	long int sec = dateTime;
	time_t time = sec;
	struct tm *tmDate = localtime(&time);
	char *buf = malloc(sizeof(char) * 80);
	strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", tmDate);
	return buf;
}
