/*
* Author: Dylan McKinney
* File: main.c
* Description: The driver of the program vector calculator. 
*              Decides whether to run minmat or print the help screen
*/

#include <string.h>
#include "ui.h"

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        print_help();
    }
    else {
        run_ui();
    }
    return 0;
}