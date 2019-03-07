//
// Created by Scaduto Enzo on 2019-03-07.
//

#include "randomError.h"
#include "failure.h"

struct plane getPlaneFromJson(char *json);
struct failure *getFailureFromJson(char *json, unsigned int nbFailure);



char *autoGeneration(int nb) {
	srand(time(NULL));
	int i = 0;
	static char json[4096];
	int date = rand();

	if (nb == 0) {
		return "";
	}

	sprintf(json, "{Id_plane:%s,Type_plane:%s,Nb_failures:%d,failures:[{", idPlane[rand()%60], typePlane[rand()%11], nb);

	while (i < nb) {
		if (i != 0)
			sprintf(json, "%s,{", json);
		sprintf(json, "%sId_failure:%d,Date:%d,Id_component:%d,Level_criticity:%d,Comment_failure_size:12,Comment_failure:Test Failure}",json,
			rand()%(0x100D-0x1000) + 0x1000, date, rand()%(0x200D-0x2000) + 0x2000, rand()%10);
		i += 1;
	}
	sprintf(json, "%s]}", json);
	//printf("%s\n", json);
	return json;
}


// Main de test
int main(int argc, char** argv)
{
	char *json = autoGeneration(3);
	struct plane pl;
	struct failure *fail;
	printf("%s\n", json);

	pl = getPlaneFromJson(autoGeneration(3));
	printf("Id Plane : %s\n", pl.id_plane);
	printf("Type Plane : %d\n", pl.type_plane);
	printf("Nb Failure : %d\n", pl.nb_failures);

	fail = getFailureFromJson(autoGeneration(3), pl.nb_failures);
	printf("criticity : %d\n", fail[0].level_criticity_failure_x);
	printf("idfailure : %d\n", fail[0].id_failure_x);
	printf("comment : %s\n", fail[0].comment_failure_x);

	int i = 0;

	while (i < pl.nb_failures) {
		printFailureToFile(fail[i], pl);
		i += 1;
	}
}