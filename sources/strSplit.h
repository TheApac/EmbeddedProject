/**
 * \file strSplit.h
 * \author ESC
 * \brief Split a string with a delimiter
 */

#ifndef EMBEDDEDPROJECT_STRSPLIT_H
#define EMBEDDEDPROJECT_STRSPLIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * \brief Split a string with a delimiter
 * \param a_str the string to split
 * \param a_delim the delimiter
 * \return an array of the split string
 */
char **str_split(char *a_str, const char a_delim);

#endif //EMBEDDEDPROJECT_STRSPLIT_H
