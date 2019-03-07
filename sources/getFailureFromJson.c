//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "getFailureFromJson.h"
#include "strSplit.h"
#include "failure.h"

char *epurStr(char *str) {
	int i = 0;
	char *buff = (char*) malloc(sizeof(char*) * strlen(str));
	int j = 0;

	if (str[i] == ',')
		i += 1;
	while (str[i]) {
		if (str[i] != '{' && str[i] != ']' && str[i] != '}') {
			buff[j] = str[i];
			j += 1;
		}
		i += 1;
	}
	return buff;
}

struct failure *getFailureFromJson(char *json, unsigned int nbFailure) {
	char *temp;
	char **tabComa;
	char** tab;
	char **tabBuf;
	struct failure *fail = malloc(sizeof(struct failure) * nbFailure + 1);
	int i = 0;
	int j = 0;

	// Get id Plane from JSON
	tabComa = str_split(json, '[');
	tabComa = str_split(tabComa[1], '}');
	while (i < nbFailure) {
	temp = epurStr(tabComa[i]);
		j = 0;
		tab = str_split(temp, ',');
		while (j < 6) {

			tabBuf = str_split(tab[j], ':');
			if (strcmp(tabBuf[0], "Id_failure") == 0)
				fail[i].id_failure_x = atoi(tabBuf[1]);
			if (strcmp(tabBuf[0], "Date") == 0)
				fail[i].datetime_failure_x = atoi(tabBuf[1]);
			if (strcmp(tabBuf[0], "Id_component") == 0)
				fail[i].id_component_failure_x = atoi(tabBuf[1]);
			if (strcmp(tabBuf[0], "Level_criticity") == 0) {
				fail[i].level_criticity_failure_x = atoi(tabBuf[1]);
				//printf("%s\n", tabBuf[0]);
			}
			if (strcmp(tabBuf[0], "Comment_failure") == 0)
				strcpy(fail[i].comment_failure_x, tabBuf[1]);
			j += 1;
		}
		//printf("Id failure: %d, Date : %d, Id Component: %d, level criticity: %d, comment failure: %s\n", fail[i].id_failure_x,
		//	   fail[i].datetime_failure_x, fail[i].id_component_failure_x, fail[i].level_criticity_failure_x, fail[i].comment_failure_x);
		i += 1;
	}
//	printf("Id failure: %d, Date : %d, Id Component: %d, level criticity: %d, comment failure: %s\n", fail[0].id_failure_x,
		//   fail[0].datetime_failure_x, fail[0].id_component_failure_x, fail[0].level_criticity_failure_x, fail[0].comment_failure_x);
	return fail;
}
