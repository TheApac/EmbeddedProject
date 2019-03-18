//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "getPlaneFromJson.h"
#include "strSplit.h"
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)


struct plane getPlaneFromJson(char *json) {
	TRY
			{
				char *temp;
				char **tabComa;
				char **tab;
				struct plane pl;

				// Get id Plane from JSON
				tabComa = str_split(json, ',');
				if (tabComa == 0 || tabComa[0] == 0) {
					printf("The json file is erroneous\n");
					strcpy(pl.id_plane, "error");
					pl.type_plane = 0;
					pl.nb_failures = 0;
					return pl;
				}
				tab = str_split(tabComa[0], ':');
				if (tab == 0 || tab[1] == 0) {
					printf("The json file is erroneous\n");
					strcpy(pl.id_plane, "error");
					pl.type_plane = 0;
					pl.nb_failures = 0;
					return pl;
				}
				strcpy(pl.id_plane, tab[1]);

				// Get type plane from JSON
				tab = str_split(tabComa[1], ':');
				pl.type_plane = atoi(tab[1]);

				// Get Nb failures
				tab = str_split(tabComa[2], ':');
				pl.nb_failures = atoi(tab[1]);

				return pl;
			}CATCH
			{
				perror("The json file is erroneous\n");
				struct plane pl;
				return pl;
			}
	ETRY;
}