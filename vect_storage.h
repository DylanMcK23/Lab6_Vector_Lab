/*
* Author: Dylan McKinney
* File: vect_storage.h
* Description: Functions for the storage array (layer 2/3)
*              Uses dynamic memory so there is no limit on vectors
*/
#ifndef VECT_STORAGE_H
#define VECT_STORAGE_H

#include "vect_math.h"

#define START_SIZE 4     // how many vectors the array holds at first

// Adds a vector (or replaces one with the same name).
// Returns 0 if it worked, -1 if we ran out of memory.
int addvect(vect new_vect);

// Looks for a vector by name. Returns 1 if found, 0 if not.
int findvect(char *name, vect *found);

// Gets the vector at a spot in the array. Returns 1 if it exists, 0 if not.
int getvect(int index, vect *found);

// Returns how many vectors are stored right now
int getcount(void);

// Frees all the memory and empties the storage
void clearvects(void);

#endif