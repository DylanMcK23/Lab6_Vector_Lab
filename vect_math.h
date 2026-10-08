/*
* Author: Dylan McKinney
* File: vect_math.h
* Description: Functions for the storage array (layer 2/3)
*/
#ifndef VECT_MATH_H
#define VECT_MATH_H

#define NAME_LEN 20      // max length of a vector name (including the \0)

// The struct of the vectors
typedef struct {
    char name[NAME_LEN];
    double x;
    double y;
    double z;
} vect;

vect add(vect a, vect b);
vect subtract(vect a, vect b);
vect scalar_mult(vect a, double num);
double dot(vect a, vect b);      // extra credit
vect cross(vect a, vect b);      // extra credit

#endif