#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>




typedef struct{
    int value;
    char* name;
} var_map;

/* create a var_map array that contains all the vars in a program */

var_map program_var[50];

/* variable used to count number of vars */
int var_count = 0;

void set_var(char* n, int v);
int get_var(char* n, int* out);




/* func used to set a variable/identifier to the var_map to be referenced when needed */

void set_var(char* n, int v){
    for(int i = 0; i < var_count; i++){
       if(strcmp(program_var[i].name, n) == 0){
            program_var[i].value = v;
            return; //break the func
           }
       }
    //create a new map to the new value set
    program_var[var_count].name = strdup(n);
    program_var[var_count].value = v;
    var_count++;
}


// func to access the var table / var map
int get_var(char* n, int* out){
    for(int i = 0; i < var_count; i++){
        if(strcmp(program_var[i].name, n) == 0){
        //get the variable and it's value if found
        *out = program_var[i].value;
        return 1;
        }
    return 0;
    }
}

//function to evaluate based of AST types and nodes, save the identifiers and do maths in C

    











