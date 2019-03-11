//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "getFailureFromJson.h"
#include "strSplit.h"
#include "failure.h"

char *epurStr(char *str) {
	int i = 0;
	int size = sizeof(char *) * strlen(str);
	//printf("%s\n",size);
	char *buff[size];
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
	char **tab;
	char **tabBuf;
	int size = sizeof(struct failure) * nbFailure + 1;
	struct failure *fail[size];
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
			if (strcmp(tabBuf[0], " \nId_failure") == 0 || strcmp(tabBuf[0], "\n\nId_failure") == 0) {

				fail[i]->id_failure_x = atoi(tabBuf[1]);
			} else if (strcmp(tabBuf[0], " Date") == 0) {
				fail[i]->datetime_failure_x = atoi(tabBuf[1]);
			} else if (strcmp(tabBuf[0], " Id_component") == 0) {
				fail[i]->id_component_failure_x = atoi(tabBuf[1]);
			} else if (strcmp(tabBuf[0], " Level_criticity") == 0) {
				fail[i]->level_criticity_failure_x = atoi(tabBuf[1]);
			} else if (strcmp(tabBuf[0], " Comment_failure") == 0) {
				strcpy(fail[i]->comment_failure_x, tabBuf[1]);
			} else if (strcmp(tabBuf[0], " Comment_failure_size") == 0) {
				strcpy(fail[i]->comment_failure_x_size, tabBuf[1]);
			}
			j += 1;
		}
		i += 1;
	}
	return fail;
}
