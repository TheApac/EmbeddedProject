//
// Created by acuevas on 11/02/19.
//
#include <string.h>

#ifndef UNTITLED6_GETFORMATTEDDATE_H
#define UNTITLED6_GETFORMATTEDDATE_H

/**
 * \brief tranform timestamp date to formated date
 * \param dateTime date in timestamp
 * \return date formated like YYYY/MM/DD-HH:mm:ss
 */
char *getFormattedDate(unsigned int dateTime, int insideFile);

#endif //UNTITLED6_GETFORMATTEDDATE_H
