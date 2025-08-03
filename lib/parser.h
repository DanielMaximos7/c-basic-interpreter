#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum{   
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_BINARY_EXPR,
    NODE_LET_STMT,
    NODE_PRINT_STMT
} NodeType;

typedef struct ASTNode {

    NodeType type;

    union{
        
        struct{
            int value;
        } number;

        struct {
            char* name;
        } identifier;
       
        //binary expression: left op right
        struct {
            struct ASTNode* left;
            char op;
            struct ASTNode* right;
        } binary;
    
        //let assignment staments "let x = expr"
        struct {
            char* name;
            struct ASTNode* value;
        } let_stmt;
        
        struct {
            struct ASTNode* expr;
        } print_stmt;

    } AstNode;

ASTNode* parse(Token* tokens, int token_count);
void print_ast(ASTNode* node, int indent);
void free_ast(ASTNode* node);

}
