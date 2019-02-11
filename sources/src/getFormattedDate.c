//
// Created by acuevas on 11/02/19.
//
#include <time.h>
#include "../include/getFormattedDate.h"

void getFormattedDate(unsigned int dateTime) {
	long int sec = dateTime;
	time_t time = sec;
	struct tm *tmDate = localtime(&time);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", tmDate);
	// print buf to file
}
