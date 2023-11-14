  #include "include/lexer.h"
#include "include/token.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MIN(a, b)   a < b ? a : b

lexer_T* lexer_init(char* src)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->current = 0;
    lexer->c = lexer->src[lexer->current];

    return lexer;
}

char lexer_peek(lexer_T* lexer, int step)
{
    return lexer->src[MIN(lexer->current + step, lexer->src_size)];
}

void lexer_advance(lexer_T* lexer)
{
    /* Literally just moves the pointer forward one step for the string */
    lexer->current++;
    lexer->c = lexer->src[lexer->current];
}

token_T* lexer_advance_current(lexer_T* lexer, int type)
{
    /* This function is only used for the "other" characters */
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    token_T* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

token_T* lexer_advance_with(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);
    return token;
}

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

void lexer_skip_whitespace(lexer_T* lexer)
{   
    while (lexer->c == 0x20 || lexer->c == 0x09 || lexer->c == 0x0D || lexer->c == 0x0A) {
        lexer_advance(lexer);
    }
}

token_T* lexer_tokenize(lexer_T* lexer)
{
    /* Main driver for the lexer */
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
                printf("[ERROR]: Expected `:=`\n");
        } break;
        case '!': {
            if (lexer_peek(lexer, 1) == '=')
                return lexer_advance_with(lexer, lexer_advance_with(lexer, init_token("!=", TOKEN_NOTEQ)));
            else
                printf("[ERROR]: Expected `!=`\n");
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
        // case EOF: return token_advance_current(lexer, TOKEN_EOF);
        default: printf("[ERROR]: Unexpected character `%c`\n", lexer->c); exit(1); break;
        }
    }

    return init_token(0, TOKEN_EOF);
}