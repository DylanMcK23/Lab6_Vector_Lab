/*
* Author: Dylan McKinney
* File: vect_math.c
* Description: Functions for the storage array (layer 2/3)
*/

#include <string.h>
#include "vect_math.h"

vect add(vect a, vect b)
{
    vect result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    strcpy(result.name, "ans");
    return result;
}

vect subtract(vect a, vect b)
{
    vect result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    strcpy(result.name, "ans");
    return result;
}

vect scalar_mult(vect a, double num)
{
    vect result;
    result.x = a.x * num;
    result.y = a.y * num;
    result.z = a.z * num;
    strcpy(result.name, "ans");
    return result;
}

// extra credit: dot product (should return a plain number)
double dot(vect a, vect b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// extra credit: cross product
vect cross(vect a, vect b)
{
    vect result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    strcpy(result.name, "ans");
    return result;
}