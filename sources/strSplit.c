//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "strSplit.h"
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)

char **str_split(char *a_str, const char a_delim) {
	char **result = 0;
	TRY
			{
				size_t count = 0;
				char *tmp = a_str;
				char *last_comma = 0;
				char delim[2];
				delim[0] = a_delim;
				delim[1] = 0;
				if (tmp == NULL) {
					return NULL;
				}
				// Count how many elements will be extracted.
				int countZ = 0;
				while (tmp[countZ]) {
					if (a_delim == tmp[countZ]) {
						count++;
						last_comma = tmp;
					}
					countZ++;
				}
				// Add space for trailing token.
				count += last_comma < (a_str + strlen(a_str) - 1);

				// Add space for terminating null string so caller knows where the list of returned strings ends.
				count++;

				result = malloc(sizeof(char *) * count);

				if (result) {
					size_t idx = 0;
					char *token = strtok(a_str, delim);
					while (token) {
						*(result + idx++) = strdup(token);
						token = strtok(0, delim);
					}
					*(result + idx) = 0;
				}
				return result;
			}
		CATCH
			{
				char **error = 0;
				return error;
			}
	ETRY;
}