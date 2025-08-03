#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    // 1. Read file contents
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

    // 2. Lex
    int token_count = 0;
    Token* tokens = tokenize_line(source, &token_count);  // or your full tokenize()
    
    print_tokens(tokens, token_count);

    // 3. Parse
    Program* prog = parse(tokens, token_count);

    // 4. Print AST
    for (int i = 0; i < prog->count; i++) {
        print_ast(prog->statements[i], 0);
    }

    // (Optional: free tokens, prog, AST nodes here)

    free(source);
    return 0;
}

