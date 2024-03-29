#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Initializes the token.
 */
token_T* init_token(char* value, int type)
{
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->value = value;
    token->type = type;

    return token;
}

/*
 * Returns a string for the token type.
 */
const char* token_type_to_str(int type)
{
    switch(type) {
    case TOKEN_ID: return "TOKEN_ID";
    case TOKEN_NUM: return "TOKEN_NUM";
    case TOKEN_COMMA: return "TOKEN_COMMA";
    case TOKEN_NOTEQ: return "TOKEN_NOTEQ";
    case TOKEN_DEFINE: return "TOKEN_DEFINE";
    case TOKEN_LPAREN: return "TOKEN_LPAREN";
    case TOKEN_RPAREN: return "TOKEN_RPAREN";
    case TOKEN_ADD: return "TOKEN_ADD";
    case TOKEN_SUB: return "TOKEN_SUB";
    case TOKEN_MUL: return "TOKEN_MUL";
    case TOKEN_DIV: return "TOKEN_DIV";
    case TOKEN_SEMI: return "TOKEN_SEMI";
    case TOKEN_PRINT: return "TOKEN_PRINT";
    case TOKEN_EOF: return "TOKEN_EOF";
    }
    return "[ERROR] Unexpected token detected.";
}

/*
 * Returns a string of the token information.
 */
char* token_to_str(token_T* token)
{
    const char* token_type_str = token_type_to_str(token->type);
    const char* template = "<type = %s, int = %d, value = `%s` >";
    char* str = calloc(strlen(template) + strlen(token_type_str) + 8, sizeof(char));

    sprintf(str, template, token_type_str, token->type, token->value);
    
    return str;
}