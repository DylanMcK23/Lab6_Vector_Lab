/*
* Author: Dylan McKinney
* File: vect_storage.c
* Description: Functions for the storage array (layer 2/3)
*/

#include <string.h>
#include "vect_storage.h"

static vect storage[MAX_VECTORS];
static int used[MAX_VECTORS];    // 1 if that spot has a vector, 0 if empty

int addvect(vect new_vect)
{
    int i;

    // first look to see if the name is already in there
    for (i = 0; i < MAX_VECTORS; i++) {
        if (used[i] == 1 && strcmp(storage[i].name, new_vect.name) == 0) {
            storage[i] = new_vect;
            return 0;
        }
    }

    // otherwise find the first empty spot
    for (i = 0; i < MAX_VECTORS; i++) {
        if (used[i] == 0) {
            storage[i] = new_vect;
            used[i] = 1;
            return 0;
        }
    }

    // no empty spots
    return -1;
}

int findvect(char *name, vect *found)
{
    int i;
    for (i = 0; i < MAX_VECTORS; i++) {
        if (used[i] == 1 && strcmp(storage[i].name, name) == 0) {
            *found = storage[i];
            return 1;
        }
    }
    return 0;
}

int getvect(int index, vect *found)
{
    if (index < 0 || index >= MAX_VECTORS) {
        return 0;
    }
    if (used[index] == 1) {
        *found = storage[index];
        return 1;
    }
    return 0;
}

void clearvects(void)
{
    int i;
    for (i = 0; i < MAX_VECTORS; i++) {
        used[i] = 0;
    }
}