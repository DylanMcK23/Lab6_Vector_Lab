/*
* Author: Dylan McKinney
* File: ui.h
* Description: The user interface (layer 3/3)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"
#include "vect_math.h"
#include "vect_storage.h"

#define LINE_LEN 200     // max length of what the user types
#define MAX_TOKENS 20    // max number of words in one command

// prints a vector like:  a = 1 2 3
void print_vect(char *name, vect v)
{
    printf("%s = %g %g %g\n", name, v.x, v.y, v.z);
}

void print_help(void)
{
    printf("minimat - a simple 3D vector calculator\n");
    printf("\n");
    printf("Usage: ./minimat        start the calculator\n");
    printf("       ./minimat -h     show this help\n");
    printf("\n");
    printf("Commands:\n");
    printf("  a = 1 2 3        make or replace vector a (commas or spaces ok)\n");
    printf("  a = 1 2          if z is left out it is 0\n");
    printf("  a                show vector a\n");
    printf("  a + b            add two vectors\n");
    printf("  a - b            subtract two vectors\n");
    printf("  a * 2  or 2 * a  multiply a vector by a number\n");
    printf("  a . b            dot product (extra credit)\n");
    printf("  a x b            cross product (extra credit)\n");
    printf("  c = a + b        do an operation and save the result in c\n");
    printf("  list             show all stored vectors\n");
    printf("  clear            erase all stored vectors\n");
    printf("  quit             exit the program\n");
    printf("\n");
    printf("NOTE: seperate each character with spaces\n");
}

// Checks if a word is one of the operators.
// Returns 1 if yes, 0 if no.
int is_operator(char *word)
{
    if (strlen(word) != 1) 
    {
        return 0;
    }
    if (word[0] == '+' || word[0] == '-' || word[0] == '*' ||
        word[0] == '.' || word[0] == 'x') 
    {
        return 1;
    }
    return 0;
}

// Checks if a word is a number. If it is, puts the number in *value.
// Returns 1 if it is a number, 0 if not.
int parse_number(char *word, double *value)
{
    char *end;
    *value = strtod(word, &end);
    if (end == word || *end != '\0') 
    {
        return 0;
    }
    return 1;
}

// Does one of the functions and puts the answer in *result.
// left and right are the words the user typed.
// Returns 0 if it worked, 1 if there was an error.
int do_operation(char *left, char *op, char *right, vect *result)
{
    vect a;
    vect b;
    double num;
    int have_a = findvect(left, &a);
    int have_b = findvect(right, &b);

    // scalar multiplication is a special case (one vector and one number)
    if (op[0] == '*') 
    {
        if (have_a == 1 && have_b == 0 && parse_number(right, &num) == 1) 
        {
            *result = scalar_mult(a, num);
        }
        else if (have_a == 0 && have_b == 1 && parse_number(left, &num) == 1) 
        {
            *result = scalar_mult(b, num);
        }
        else 
        {
            printf("Error: * needs one stored vector and one number\n");
            return 1;
        }
        return 0;
    }

    // everything else needs two vectors that exist
    if (have_a == 0) 
    {
        printf("Error: vector %s does not exist\n", left);
        return 1;
    }
    if (have_b == 0) 
    {
        printf("Error: vector %s does not exist\n", right);
        return 1;
    }

    if (op[0] == '+') 
    {
        *result = add(a, b);
    }
    else if (op[0] == '-') 
    {
        *result = subtract(a, b);
    }
    else if (op[0] == 'x') 
    {
        *result = cross(a, b);
    }
    return 0;
}

// Does the dot product and puts the answer in *answer.
// Returns 0 if it worked, 1 if there was an error.
int do_dot(char *left, char *right, double *answer)
{
    vect a;
    vect b;

    if (findvect(left, &a) == 0) 
    {
        printf("Error: vector %s does not exist\n", left);
        return 1;
    }
    if (findvect(right, &b) == 0) 
    {
        printf("Error: vector %s does not exist\n", right);
        return 1;
    }
    *answer = dot(a, b);
    return 0;
}

// Handles:  var1 op var2 
void handle_expression(char *left, char *op, char *right)
{
    vect result;
    double scalar;

    if (op[0] == '.') 
    {
        if (do_dot(left, right, &scalar) == 0) 
        {
            printf("ans = %g\n", scalar);
        }
    }
    else {
        if (do_operation(left, op, right, &result) == 0) 
        {
            print_vect("ans", result);
        }
    }
}

// Handles:  result = var1 op var2  
void handle_op_assign(char *name, char *left, char *op, char *right)
{
    vect result;

    // a dot product is a number, not a vector, so we can't save it as a vector
    if (op[0] == '.') 
    {
        printf("Error: a dot product is a number, it can't be saved as a vector\n");
        return;
    }

    if (strlen(name) >= NAME_LEN || isalpha(name[0]) == 0) 
    {
        printf("Error: bad vector name\n");
        return;
    }

    if (do_operation(left, op, right, &result) == 1) 
    {
        return;
    }

    strcpy(result.name, name);
    if (addvect(result) == -1) 
    {
        printf("Error: memory full, could not save %s\n", name);
    }
    print_vect(name, result);   // show it either way
}

// Handles:  name = 1 2 3
// words[0] is the name, words[1] is "=", the numbers start at words[2]
void handle_assignment(char *words[], int count)
{
    vect new_vect;
    double values[3] = {0.0, 0.0, 0.0};   // z defaults to 0
    int num_values = count - 2;
    int i;

    if (num_values < 2 || num_values > 3) 
    {
        printf("Error: invalid assignment, use  name = x y z\n");
        return;
    }
    if (strlen(words[0]) >= NAME_LEN || isalpha(words[0][0]) == 0) 
    {
        printf("Error: bad vector name\n");
        return;
    }

    for (i = 0; i < num_values; i++) 
    {
        if (parse_number(words[i + 2], &values[i]) == 0) 
        {
            printf("Error: '%s' is not a number\n", words[i + 2]);
            return;
        }
    }

    strcpy(new_vect.name, words[0]);
    new_vect.x = values[0];
    new_vect.y = values[1];
    new_vect.z = values[2];

    if (addvect(new_vect) == -1) 
    {
        printf("Error: memory full, could not save %s\n", words[0]);
        return;
    }
    print_vect(new_vect.name, new_vect);
}

// Handles typing just a name
void handle_display(char *name)
{
    vect v;
    if (findvect(name, &v) == 1) 
    {
        print_vect(v.name, v);
    }
    else 
    {
        printf("Vector %s does not exist\n", name);
    }
}

// The list command
void handle_list(void)
{
    vect v;
    int i;
    int count = 0;

    for (i = 0; i < MAX_VECTORS; i++) 
    {
        if (getvect(i, &v) == 1) 
        {
            print_vect(v.name, v);
            count++;
        }
    }
    if (count == 0) 
    {
        printf("No vectors stored\n");
    }
}

// The main loop: read a line, split it into words, figure out what it is
void run_ui(void)
{
    char line[LINE_LEN];
    char *words[MAX_TOKENS];
    char *word;
    int count;
    int i;

    while (1) {
        printf("minimat> ");

        // fgets gives NULL at end of input (like ctrl+d) so we quit then
        if (fgets(line, LINE_LEN, stdin) == NULL) 
        {
            printf("\n");
            break;
        }

        // turn commas, newlines, and \r into spaces so strtok can split it
        for (i = 0; line[i] != '\0'; i++) 
        {
            if (line[i] == ',' || line[i] == '\n' || line[i] == '\r') 
            {
                line[i] = ' ';
            }
        }

        // split the line into words
        count = 0;
        word = strtok(line, " \t");
        while (word != NULL && count < MAX_TOKENS) 
        {
            words[count] = word;
            count++;
            word = strtok(NULL, " \t");
        }

        if (word != NULL) 
        {
            printf("Error: too many words in that command\n");
            continue;
        }

        // blank line, just ask again
        if (count == 0) 
        {
            continue;
        }

        // now decide what the user typed
        if (count == 1) 
        {
            if (strcmp(words[0], "quit") == 0) 
            {
                break;
            }
            else if (strcmp(words[0], "clear") == 0) 
            {
                clearvects();
                printf("Memory cleared\n");
            }
            else if (strcmp(words[0], "list") == 0) 
            {
                handle_list();
            }
            else 
            {
                handle_display(words[0]);
            }
        }
        else if (count == 3 && is_operator(words[1]) == 1) 
        {
            // example: a + b
            handle_expression(words[0], words[1], words[2]);
        }
        else if (count >= 3 && strcmp(words[1], "=") == 0) {
            if (count == 5 && is_operator(words[3]) == 1) 
            {
                // example: c = a + b
                handle_op_assign(words[0], words[2], words[3], words[4]);
            }
            else 
            {
                // example: a = 1 2 3
                handle_assignment(words, count);
            }
        }
        else 
        {
            printf("Error: Command not understood (try -h for help)\n");
        }
    }
}