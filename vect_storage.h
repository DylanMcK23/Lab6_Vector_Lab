/*
* Author: Dylan McKinney
* File: vect_storage.h
* Description: Functions for the storage array (layer 2/3)
*/
#ifndef VECT_STORAGE_H
#define VECT_STORAGE_H

#include "vect_math.h"

#define MAX_VECTORS 10   // we can only store 10 vectors

int addvect(vect new_vect);

int findvect(char *name, vect *found);

int getvect(int index, vect *found);

// Empties the storage
void clearvects(void);

#endif