#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <source-file>\n", argv[0]);
        return 1;
    }


    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* source = malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);

   
    int token_count = 0;
    Token* tokens = tokenize_line(source, &token_count); 
    
    print_tokens(tokens, token_count);

  
    Program* prog = parse(tokens, token_count);

 
    for (int i = 0; i < prog->count; i++) {
        print_ast(prog->statements[i], 0);
    }

    free(source);
    return 0;
}

