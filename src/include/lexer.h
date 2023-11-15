#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stdlib.h>

typedef struct LEXER_STRUCT {
    char* src;              /* Buffer */
    size_t src_size;        /* Size of the buffer */
    unsigned int current;   /* Pointer to the current character in the buffer */
    char c;                 /* The current character */
} lexer_T;

lexer_T* lexer_init(char* src);                 /* Initializes the lexer */

char lexer_peek(lexer_T* lexer, int step);      /* Looks one character ahead */

void lexer_advance(lexer_T* lexer);             /* Moves the lexer to the next character */

token_T* lexer_advance_current(lexer_T* lexer, int type);       /* Moves the lexer forward for the given symbol */

token_T* lexer_advance_with(lexer_T* lexer, token_T* token);    /* Moves the lexer forward with the given token */

token_T* lexer_parse_id(lexer_T* lexer);    /* Returns the token for multi-character identifiers */

token_T* lexer_parse_num(lexer_T* lexer);   /* Returns the token for multi-character numbers */

void lexer_skip_whitespace(lexer_T* lexer); /* Skips whitespace characters */

token_T* lexer_tokenize(lexer_T* lexer);    /* Drives the lexer*/

#endif