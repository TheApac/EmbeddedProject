//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "randomError.h"


char *autoGeneration(int nb) {
	srand(time(NULL));
	int i = 0;
	static char json[4096];

	if (nb == 0) {
		return "";
	}

	sprintf(json, "{ Id_plane: %s, Type_plane: %s, Nb_failures: %d, failures: [ { ", idPlane[rand()%60], typePlane[rand()%11], nb);

	while (i < nb) {
		if (i != 0)
			sprintf(json, "%s,{", json);
		sprintf(json, "%s Id_failure: %d, Date: %d, Id_component: %d, Level_criticity: %d, Comment_failure_size: 12, Comment_failure: Test Failure }",json,
			rand()%(0x100D-0x1000) + 0x1000, rand(), rand()%(0x200D-0x2000) + 0x2000, rand()%10);
		i += 1;
	}
	sprintf(json, "%s] }", json);
	//printf("%s\n", json);
	return json;
}
/*
int main(int argc, char** argv)
{
	printf("%s\n", autoGeneration(2));
}*/