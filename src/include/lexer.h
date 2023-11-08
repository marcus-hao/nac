#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stdlib.h>

typedef struct LEXER_STRUCT {
    char* src;
    size_t src_size;
    unsigned int current;
    char c;
} lexer_T;

lexer_T* lexer_init(char* src);

char lexer_peek(lexer_T* lexer, int step);

void lexer_advance(lexer_T* lexer);

token_T* lexer_advance_current(lexer_T* lexer, int type);

token_T* lexer_advance_with(lexer_T* lexer, token_T* token);

token_T* lexer_parse_id(lexer_T* lexer);

token_T* lexer_parse_num(lexer_T* lexer);

void lexer_skip_whitespace(lexer_T* lexer);

token_T* lexer_tokenize(lexer_T* lexer);

#endif