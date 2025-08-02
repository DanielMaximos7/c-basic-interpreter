#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 64

Token make_token(TokenType type, const char* value){
	Token token;
	token.type = type;

	if(value) {
		token.value = strdup(value);
	} else {
		token.value = NULL;
	}

	return token;
}

TokenType keyword_type(const char* str){
	if(strcmp(str, "let") == 0) return TOKEN_LET;
	if(strcmp(str, "print") == 0) return TOKEN_PRINT;
	return TOKEN_IDENTIFIER;
}


Token* tokenize_line(const char* line, int* out_token_count){

	Token* tokens = malloc(sizeof(Token) * MAX_TOKENS);

	int count = 0;
	int i = 0;

	while(line[i]){
		if(isspace(line[i])){
			i++;
			continue;
		}

		
		if(isalpha(line[i])){
			int start = i;
			while(isalnum(line[i])) i++;

			int length = i - start;
			char* word = strndup(&line[start], length);

			TokenType type = keyword_type(word);
			tokens[count++] = make_token(type, type == TOKEN_INDENTIFIER ? word : NULL);
			free(word);
			continue;

		}
		
		if(isdigit(line[i])){
			int start = i;
			while(isdigit(line[i])) i++;

			int length = i - start;
			char* num = strndup(&line[start], length);

			tokens[count++] = make_token(TOKEN_NUMBER, num);
			free(num);
			continue;


		}

		switch(line[i]){
			case '=': tokens[count++] = make_token(TOKEN_EQUAL, NULL); break;
			case '+': tokens[count++] = make_token(TOKEN_PLUS, NULL); break;
			case '-': tokens[count++] = make_token(TOKEN_MINUS, NULL); break;
			case '*': tokens[count++] = make_token(TOKEN_STAR, NULL); break;
			case '/': tokens[count++] = make_token(TOKEN_SLASH, NULL); break;
			case '(': tokens[count++] = make_token(TOKEN_LPAREN, NULL); break;
			case ')': tokens[count++] = make_token(TOKEN_RPAREN, NULL); break;
			default:
                		tokens[count++] = make_token(TOKEN_INVALID, NULL);
                		break;
		}
          
		i++;
	}

	tokens[count++] = make_token(TOKEN_EOF, NULL); 
	*out_token_count = count;
	return tokens;
	
}
