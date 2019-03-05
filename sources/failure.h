//
// Created by acuevas on 11/02/19.
//

#ifndef UNTITLED6_FAILURE_H
#define UNTITLED6_FAILURE_H

#define MAX_COMMENT_SIZE 1000

struct Failure

{
    unsigned int datetime_failure_x;

    unsigned int id_failure_x;

    unsigned int id_component_failure_x;

    unsigned int comment_failure_x_size[MAX_COMMENT_SIZE];

    unsigned int level_criticity_failure_x;

    unsigned char comment_failure_x[MAX_COMMENT_SIZE];

};

void printFailureToFile(Failure* failure);

#endif //UNTITLED6_FAILURE_H
