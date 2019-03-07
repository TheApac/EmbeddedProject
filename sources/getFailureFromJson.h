//
// Created by Scaduto Enzo on 2019-03-07.
//

#ifndef EMBEDDEDPROJECT_GETFAILUREFROMJSON_H
#define EMBEDDEDPROJECT_GETFAILUREFROMJSON_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct failure *getFailureFromJson(char *json, unsigned int nbFailure);

#endif //EMBEDDEDPROJECT_GETFAILUREFROMJSON_H
