/**
 * \file failure.h
 * \author BSU
 * \brief Define failure structure and the function to print the failure in a file
 */
#ifndef UNTITLED6_FAILURE_H
#define UNTITLED6_FAILURE_H

#define MAX_COMMENT_SIZE 1000

#include "plane.h"

unsigned int nbFailure = 0;

/**
 * \struct failure
 * \brief Object that contain all information about failure
 *
 * failure contain the date of the failure,
 * the id of the failure,
 * the id of the component failure,
 * a max size failure comment,
 * the failure level criticity
 * a failure comment
 */
struct failure
{
    unsigned int datetime_failure_x;

    unsigned int id_failure_x;

    unsigned int id_component_failure_x;

    unsigned int comment_failure_x_size[MAX_COMMENT_SIZE];

    unsigned int level_criticity_failure_x;

    unsigned char comment_failure_x[MAX_COMMENT_SIZE];

};

/**
 * \brief print a failure in a file
 * \param fail failure structure to print
 * \param pl plane structure
 */
void printFailureToFile(struct failure fail, struct plane pl);

#endif //UNTITLED6_FAILURE_H
