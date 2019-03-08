//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "getPlaneFromJson.h"
#include "strSplit.h"


struct plane getPlaneFromJson(char *json) {
	char *temp;
	char **tabComa;
	char **tab;
	struct plane pl;

	// Get id Plane from JSON
	tabComa = str_split(json, ',');
	tab = str_split(tabComa[0], ':');
	strcpy(pl.id_plane, tab[1]);

	// Get type plane from JSON
	tab = str_split(tabComa[1], ':');
	pl.type_plane = atoi(tab[1]);

	// Get Nb failures
	tab = str_split(tabComa[2], ':');
	pl.nb_failures = atoi(tab[1]);

	return pl;
}