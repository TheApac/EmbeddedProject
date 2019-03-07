/**
 * \file plane.h
 * \author JCH
 * \brief Contain the structure of a plane
 */
#ifndef UNTITLED6_PLANE_H
#define UNTITLED6_PLANE_H

/**
 * \struct plane
 * \brief Structure of a plane
 *
 * Plane contain an array that represent the id of the plane,
 * current number of failures,
 * decimal value of the type of plane
 */
struct plane
{
    unsigned char id_plane[12];

    unsigned int nb_failures;

    unsigned int type_plane;

};

#endif //UNTITLED6_PLANE_H
