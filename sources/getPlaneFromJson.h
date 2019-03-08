/**
 * \file getPlaneFromJson.h
 * \author ESC
 * \brief Return a plane struct from the Json given in parameter
 */

#ifndef EMBEDDEDPROJECT_GETPLANEFROMJSON_H
#define EMBEDDEDPROJECT_GETPLANEFROMJSON_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plane.h"

/**
 * \brief Return a plane struct from the Json given in parameter
 * \param json A Jsonish string with all informations
 * \return a plane struct
 */
struct plane getPlaneFromJson(char *json);

#endif //EMBEDDEDPROJECT_GETPLANEFROMJSON_H
