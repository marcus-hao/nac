  #include "include/lexer.h"
#include "include/token.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MIN(a, b)   a < b ? a : b   /** Returns the minimum between two variables */

/*
 * This function takes in an input buffer and initializes the lexer with it.
 */
lexer_T* init_lexer(char* src)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->current = 0;
    lexer->c = lexer->src[lexer->current];

    return lexer;
}

/*
 * Looks `step` characters ahead of the current character and returns it
 * if it is within the bounds of the buffer.
 * 
 * This function is used for scanning the `:=` token.
 */
char lexer_peek(lexer_T* lexer, int step)
{
    return lexer->src[MIN(lexer->current + step, lexer->src_size)];
}

/*
 * Moves the lexer one character forward.
 */
void lexer_advance(lexer_T* lexer)
{
    /* Literally just moves the pointer forward one step for the string */
    lexer->current++;
    lexer->c = lexer->src[lexer->current];
}

/*
 * Moves the lexer one character forward and returns the token.
 * This function is only used for the symbols `+`, `-`, `*`, `/`,
 * `(`, `)`, `,`, `;`.
 */
token_T* lexer_advance_current(lexer_T* lexer, int type)
{
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    token_T* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

/*
 * Moves the lexer one character forward when it is passed with the given
 * token. The token passed is also returned.
 * 
 * This function is to be used when scanning the `:=` and `!=` tokens.
 */
token_T* lexer_advance_with(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);
    return token;
}

/* 
 * Returns an identifer with multiple-characters.
 */
token_T* lexer_parse_id(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));

    while (isalnum(lexer->c)) {
        value = realloc(value, strlen(value) + 2 * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    if (strcmp(value, PRINT_KEYWORD)  == 0)
        return init_token(value, TOKEN_PRINT);

    return init_token(value, TOKEN_ID);
}

/*
 * Returns a number with multiple-characters. 
 */
token_T* lexer_parse_num(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));

    while (isdigit(lexer->c)) {
        value = realloc(value, strlen(value) + 2 * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    return init_token(value, TOKEN_NUM);
}

/*
 * Skips whitespace characters.
 */
void lexer_skip_whitespace(lexer_T* lexer)
{   
    while (lexer->c == 0x20 || lexer->c == 0x09 || lexer->c == 0x0D || lexer->c == 0x0A) {
        lexer_advance(lexer);
    }
}

/*
 * Begins tokenizing the characters.
 * 
 * This is the main driver of the lexer.
 */
token_T* lexer_tokenize(lexer_T* lexer)
{
    while (lexer->c != '\0') {
        lexer_skip_whitespace(lexer);

        if (isalpha(lexer->c))
            return lexer_parse_id(lexer);
        
        if (isdigit(lexer->c))
            return lexer_parse_num(lexer);

        switch (lexer->c) {
        case ':': {
            if (lexer_peek(lexer, 1) == '=')
                return lexer_advance_with(lexer, lexer_advance_with(lexer, init_token(":=", TOKEN_DEFINE)));
            else
                printf("[IllegalToken]: Expected `:=`\n");
        } break;
        case '!': {
            if (lexer_peek(lexer, 1) == '=')
                return lexer_advance_with(lexer, lexer_advance_with(lexer, init_token("!=", TOKEN_NOTEQ)));
            else
                printf("[IllegalToken]: Expected `!=`\n");
        } break;
        case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
        case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
        case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
        case '+': return lexer_advance_current(lexer, TOKEN_ADD);
        case '-': return lexer_advance_current(lexer, TOKEN_SUB);
        case '*': return lexer_advance_current(lexer, TOKEN_MUL);
        case '/': return lexer_advance_current(lexer, TOKEN_DIV);
        case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
        case '\0': break;
        default: printf("[IllegalToken]: Unexpected character `%c`\n", lexer->c); exit(1); break;
        }
    }

    return init_token(0, TOKEN_EOF);
}