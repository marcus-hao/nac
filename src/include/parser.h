#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "token.h"

typedef struct PARSER_STRUCT {
    lexer_T* lexer;
    token_T* token;     // holds the lookahead token
} parser_T;

parser_T* init_parser(lexer_T* lexer);

token_T* parser_eat(parser_T* parser, int type);

AST_T* parser_parse_program(parser_T* parser);

AST_T* parser_parse_stmt_list(parser_T* parser);

AST_T* parser_parse_stmt(parser_T* parser);

AST_T* parser_parse_stmt_list_prime(parser_T* parser);

AST_T* parser_parse_print(parser_T* parser);

AST_T* parser_parse_assignment(parser_T* parser);

AST_T* parser_parse_T(parser_T* parser);

AST_T* parser_parse_F(parser_T* parser);

AST_T* parser_parse_Tprime(parser_T* parser);

AST_T* parser_parse_E(parser_T* parser);

AST_T* parser_parse_Eprime(parser_T* parser);

#endif