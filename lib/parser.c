#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Token* tokens;
static int current;
static int total;

static Token peek(){
    return tokens[current];
}

static Token advance(){
    return tokens[current++];
}

static int match(TokenType type){
    if(peek().type == type){
        advance();
        return 1;
    }
    return 0;
}

static Token previous(){
    return current > 0 ? tokens[current - 1] : tokens[0];
}

// == Parser Entry Point == 
Program* parse(Token* input_tokens, int count);

// == Statement Parsers == 
ASTNode* parse_print_stmt();
ASTNode* parse_let_stmt();

// == Expression Parsers ==
ASTNode* parse_expression();
ASTNode* parse_primary();

// == AST Constructors ==
ASTNode* make_number_node(int value);
ASTNode* make_identifier_node(char* name);


Program* parse(Token* input_tokens, int count){
    tokens = input_tokens;
    current = 0;
    total = count;

    Program* program = malloc(sizeof(Program));
    program->statements = malloc(sizeof(ASTNode*) * 128);
    program->count = 0;

    while(peek().type != TOKEN_EOF){
        ASTNode* stmt = NULL;

        if(peek().type == TOKEN_LET){
            stmt = parse_let_stmt();
        }else if(peek().type == TOKEN_PRINT){
            stmt = parse_print_stmt();
        }

        if(!stmt){
            break;
        }

        program->statements[program->count++] = stmt;
        
        if(peek().type == TOKEN_SEMICOLON){
            advance();
        }

    }
    
    return program;

}


ASTNode* parse_let_stmt(){
    if(peek().type == TOKEN_LET){
        advance();
    }else {
        return NULL;
    }

    char* name = strdup(advance().value);
   
    if(!match(TOKEN_EQUAL)) return NULL;

    ASTNode* value = parse_expression();

    if(!value) return NULL;

    ASTNode* let = malloc(sizeof(ASTNode));
    let->type = NODE_LET_STMT;
    let->ASTNode.let_stmt.name = name;
    let->ASTNode.let_stmt.value = value;

    return let;

}

ASTNode* parse_print_stmt(){
    advance(); //consuming print
    
    if(!match(TOKEN_LPAREN)){
        return NULL;
    }

    ASTNode* expr = parse_expression(); //parse inside print
    
    if(!match(TOKEN_RPAREN)){
        return NULL;
    }

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT_STMT;
    node->ASTNode.print_stmt.expr = expr;
    return node;
    
}

// Parse a number or simple binary expression (e.g. 10 + 3)
ASTNode* parse_expression(){

   ASTNode* left = parse_primary();
   if(!left) return NULL;

   while(peek().type == TOKEN_PLUS || peek().type == TOKEN_MINUS){
        printf("Operator token at index %d: type=%d, value=%s\n", current, peek().type, peek().value);       
        Token op_token = advance();

        char op;

        switch(op_token.type){
            case TOKEN_PLUS:    op = '+'; break;
            case TOKEN_MINUS:   op = '-'; break;
            default:            op = '?'; break;
        }

        ASTNode* right = parse_primary();

        if(!right) return NULL;

        ASTNode* binary = malloc(sizeof(ASTNode));
        binary->type = NODE_BINARY_EXPR;
        binary->ASTNode.binary.left = left;
        binary->ASTNode.binary.op = op;
        binary->ASTNode.binary.right = right;
    
        left = binary; // allows chaining (x + 5) - 2 -?
    }
  
   return left;
}


ASTNode* parse_primary(){
    if(match(TOKEN_NUMBER)){
        int value = atoi(previous().value);
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_NUMBER;
        node->ASTNode.number.value = value;
        return node;
    }

    if(match(TOKEN_IDENTIFIER)){
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_IDENTIFIER;
        node->ASTNode.identifier.name = strdup(previous().value);
        return node;
    }

    return NULL;

}

ASTNode* make_number_node(int value){
    
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->ASTNode.number.value = value;
    return node;

}

ASTNode* make_identifier_node(char* name){
    
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->ASTNode.identifier.name = name ? strdup(name) : NULL;
    return node;
}

void print_ast(ASTNode* node, int indent) {
    if (!node) return;

    // helper to indent
    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NODE_NUMBER:
            printf("Number: %d\n", node->ASTNode.number.value);
            break;

        case NODE_IDENTIFIER:
            printf("Identifier: %s\n", node->ASTNode.identifier.name);
            break;

        case NODE_BINARY_EXPR:
            printf("BinaryExpr: '%c'\n", node->ASTNode.binary.op);
            print_ast(node->ASTNode.binary.left, indent + 1);
            print_ast(node->ASTNode.binary.right, indent + 1);
            break;

        case NODE_LET_STMT:
            printf("LetStmt: %s =\n", node->ASTNode.let_stmt.name);
            print_ast(node->ASTNode.let_stmt.value, indent + 1);
            break;

        case NODE_PRINT_STMT:
            printf("PrintStmt:\n");
            print_ast(node->ASTNode.print_stmt.expr, indent + 1);
            break;
    }
}


