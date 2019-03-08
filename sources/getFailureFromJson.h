/**
 * \file getFailureFromJson.h
 * \author ESC
 * \brief Return a failure struct from the Json given in parameter
 */

#ifndef EMBEDDEDPROJECT_GETFAILUREFROMJSON_H
#define EMBEDDEDPROJECT_GETFAILUREFROMJSON_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \brief Return a plane failure from the Json given in parameter
 * \param json A Jsonish string with all informations
 * \param nbFailure The number of failure to return
 * \return a failure struct
 */
struct failure *getFailureFromJson(char *json, unsigned int nbFailure);

#endif //EMBEDDEDPROJECT_GETFAILUREFROMJSON_H
