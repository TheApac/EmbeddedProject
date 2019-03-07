/**
 * \file getFormattedDate.h
 * \author ACU
 * \brief Transform a date from timestamp to YYYY/MM/DD-HH:mm:ss format
 */
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
