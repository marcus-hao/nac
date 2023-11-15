#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "token.h"

typedef struct PARSER_STRUCT {
    lexer_T* lexer;     /* Lexer */
    token_T* token;     /* The current token */
} parser_T;

parser_T* init_parser(lexer_T* lexer);                  /* Initializes the parser */

token_T* parser_eat(parser_T* parser, int type);        /* Eats the current token */

AST_T* parser_parse_program(parser_T* parser);          /* Parses <program> */

AST_T* parser_parse_stmt_list(parser_T* parser);        /* Parses <stmt_list> */

AST_T* parser_parse_stmt(parser_T* parser);             /* Parses <stmt> */

AST_T* parser_parse_stmt_list_prime(parser_T* parser);  /* Parses <stmt_list_prime> */

AST_T* parser_parse_print(parser_T* parser);            /* Parses <print> */

AST_T* parser_parse_assignment(parser_T* parser);       /* Parses <assignment> */

AST_T* parser_parse_T(parser_T* parser);                /* Parses <T> */

AST_T* parser_parse_F(parser_T* parser);                /* Parses <F> */

AST_T* parser_parse_Tprime(parser_T* parser);           /* Parses <Tprime> */

AST_T* parser_parse_E(parser_T* parser);                /* Parses <E> */

AST_T* parser_parse_Eprime(parser_T* parser);           /* Parses <Eprime> */

#endif