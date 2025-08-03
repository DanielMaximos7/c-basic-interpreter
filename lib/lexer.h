#ifndef LEXER_H
#define LEXER_H

typedef enum{
	TOKEN_LET,
	TOKEN_PRINT,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_EQUAL,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF,
	TOKEN_INVALID
} TokenType;

typedef struct {
	TokenType type;
	char* value; //identifier names or number strings
} Token;

Token* tokenize_line(const char* line, int* out_token_count);

void print_tokens(Token* tokens, int count);


#endif // LEXER_H
