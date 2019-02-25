//
// Created by acuevas on 11/02/19.
//
#include <time.h>
#include "../include/getFormattedDate.h"
#include <stdio.h>

void getFormattedDate(unsigned int dateTime) {
	long int sec = dateTime;
	time_t time = sec;
	struct tm *tmDate = localtime(&time);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", tmDate);
	FILE *pFile2;
	pFile2 = fopen("log", "a");
	fprintf(pFile2, buf);
	fprintf(pFile2, "\n");
	fclose(pFile2);
}
