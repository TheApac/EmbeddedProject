//
// Created by Scaduto Enzo on 2019-03-07.
//
#include "getFailureFromJson.h"
#include "strSplit.h"
#include "failure.h"
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)

char *epurStr(char *str) {
	int len = strlen(str);
	int i = 0;
	int j;
	for (i = 0; i < len; i++) {
		if (str[i] == '{' || str[i] == ']' || str[i] == '}') {
			for (j = i; j < len; j++) {
				str[j] = str[j + 1];
			}
			len--;
			i--;
		}
	}
	str[strlen(str)] = '\0';
	return str;
}

struct failure *getFailureFromJson(char *json, unsigned int nbFailure) {
	TRY
			{
				char *temp;
				char **tabComa;
				char **tab;
				char **tabBuf;
				int size = sizeof(struct failure) * nbFailure + 1;
				struct failure *fails = malloc(sizeof(struct failure) * nbFailure + 1);
				int i = 0;
				int j = 0;

				// Get id Plane from JSON
				tabComa = str_split(json, '[');
				if (tabComa == NULL) {
					printf("The json file is erroneous\n");
					return NULL;
				}
				tabComa = str_split(tabComa[1], '}');
				if (tabComa == NULL) {
					printf("The json file is erroneous\n");
					return NULL;
				}
				while (i < nbFailure) {
					temp = epurStr(tabComa[i]);
					j = 0;
					tab = str_split(temp, ',');
					if (tab == NULL) {
						printf("The json file is erroneous\n");
						return NULL;
					}
					struct failure fail;
					while (j < 6) {
						if (tab[j] == 0) {
							printf("The json file is erroneous\n");
							return NULL;
						}
						tabBuf = str_split(tab[j], ':');
						if (tabBuf == NULL) {
							printf("The json file is erroneous\n");
							return NULL;
						}
						if (strcmp(tabBuf[0], " \nId_failure") == 0 ||
						    strcmp(tabBuf[0], "\n\nId_failure") == 0) {
							fail.id_failure_x = atoi(tabBuf[1]);
						} else if (strcmp(tabBuf[0], " Date") == 0) {
							fail.datetime_failure_x = atoi(tabBuf[1]);
						} else if (strcmp(tabBuf[0], " Id_component") == 0) {
							fail.id_component_failure_x = atoi(tabBuf[1]);
						} else if (strcmp(tabBuf[0], " Level_criticity") == 0) {
							fail.level_criticity_failure_x = atoi(tabBuf[1]);
						} else if (strcmp(tabBuf[0], " Comment_failure") == 0) {
							strcpy(fail.comment_failure_x, tabBuf[1]);
						} else if (strcmp(tabBuf[0], " Comment_failure_size") == 0) {
							strcpy(fail.comment_failure_x_size, tabBuf[1]);
						}
						j += 1;
					}
					fails[i] = fail;
					i += 1;
				}
				return fails;
			}

		CATCH
			{
				printf("The json file is erroneous\n");
				return NULL;
			}
	ETRY;
}