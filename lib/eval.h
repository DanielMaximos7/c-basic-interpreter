#ifndef EVAL_H
#define EVAL_H

#include "parser.h"

typedef struct Value{
    enum { VAL_INT } type;
    union{
        int int_val;
    };
} Value;

Value evaluate(ASTNode* node);

#endif
