/*
* Author: Dylan McKinney
* File: vect_storage.c
* Description: Functions for the storage array (layer 2/3)
*              The vectors are kept in a dynamic array that grows
*              with realloc when it gets full.
*/

#include <stdlib.h>
#include <string.h>
#include "vect_storage.h"

static vect *storage = NULL;   // the dynamic array (NULL when empty)
static int count = 0;          // how many vectors are in the array
static int capacity = 0;       // how many vectors the array has room for

int addvect(vect new_vect)
{
    int i;
    int new_capacity;
    vect *temp;

    // first look to see if the name is already in there
    for (i = 0; i < count; i++) {
        if (strcmp(storage[i].name, new_vect.name) == 0) {
            storage[i] = new_vect;
            return 0;
        }
    }

    // if the array is full make it bigger
    if (count == capacity) {
        if (capacity == 0) {
            new_capacity = START_SIZE;
        }
        else {
            new_capacity = capacity * 2;
        }

        // use a temp pointer so we don't lose the old array if realloc fails
        temp = realloc(storage, new_capacity * sizeof(vect));
        if (temp == NULL) {
            return -1;
        }
        storage = temp;
        capacity = new_capacity;
    }

    storage[count] = new_vect;
    count++;
    return 0;
}

int findvect(char *name, vect *found)
{
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(storage[i].name, name) == 0) {
            *found = storage[i];
            return 1;
        }
    }
    return 0;
}

int getvect(int index, vect *found)
{
    if (index < 0 || index >= count) {
        return 0;
    }
    *found = storage[index];
    return 1;
}

int getcount(void)
{
    return count;
}

void clearvects(void)
{
    free(storage);
    storage = NULL;
    count = 0;
    capacity = 0;
}