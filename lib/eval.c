#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "eval.h"

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
Value evaluate(ASTNode* node);

Value evaluate(ASTNode* node){   
    Value v;
    switch(node->type){
        case NODE_NUMBER:
            Value integer;
            integer.type = VAL_INT;
            integer.int_val = node->ASTNode.number.value;
            return integer;
      
        case NODE_IDENTIFIER:
            int test;
            if(get_var(node->ASTNode.identifier.name, &test) == 0){
                set_var(node->ASTNode.identifier.name, 0);       
            }
            int val;
            get_var(node->ASTNode.identifier.name, &val);        
            v.type = VAL_INT;
            v.int_val = val;
            return v;
        
        case NODE_BINARY_EXPR:
            int result;
            Value left =  evaluate(node->ASTNode.binary.left);
            Value right = evaluate(node->ASTNode.binary.right);

            switch(node->ASTNode.binary.op){
                case '+':
                    result = left.int_val + right.int_val;
                    break;
                case '-':
                    result = left.int_val - right.int_val;
                    break;
            }               
            v.type = VAL_INT;
            v.int_val = result;
            return v;

        case NODE_LET_STMT:
            Value value = evaluate(node->ASTNode.let_stmt.value);
            char* n = node->ASTNode.let_stmt.name;
            set_var(n, value.int_val);

        case NODE_PRINT_STMT:
            evaluate(node->ASTNode.print_stmt.expr);
            
    }
}
/* func used to set a variable/identifier to the var_map to be referenced when needed */
void set_var(char* n, int v){
    for(int i = 0; i < var_count; i++){
       if(strcmp(program_var[i].name, n) == 0){
            program_var[i].value = v;
            return; //break the func
           }
       }   
    program_var[var_count].name = strdup(n);
    program_var[var_count].value = v;
    var_count++;
}

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



    











