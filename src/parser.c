#include "include/AST.h"
#include "include/parser.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

token_T* temp_token;    // Quick hack

parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_tokenize(lexer);

    return parser;
}

token_T* parser_eat(parser_T* parser, int type)
{
    if (parser->token == NULL) {
        printf("[ERROR] Unexpected end of input.\n");
        exit(1);
    }
    
    if (parser->token->type != type) {
        printf("[ERROR] Unexpected token `%s`, did you mean `%s`?\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

    token_T* eaten_token = parser->token;
    parser->token = lexer_tokenize(parser->lexer);

    return eaten_token;
}

AST_T* parser_parse_program(parser_T* parser)
{
    return parser_parse_stmt_list(parser);
}

AST_T* parser_parse_stmt_list(parser_T* parser)
{
    AST_T* stmt = parser_parse_stmt(parser);
    AST_T* stmt_list_prime = parser_parse_stmt_list_prime(parser);

    return init_ast(NULL, stmt, stmt_list_prime);
}

AST_T* parser_parse_stmt(parser_T* parser)
{
    if (parser->token->type == TOKEN_PRINT) {
        return parser_parse_print(parser);
    } else if (parser->token->type == TOKEN_ID) {
        parser_eat(parser, TOKEN_ID);

        if (parser->token->type == TOKEN_DEFINE) {
            return parser_parse_assignment(parser);
        }
        
        return parser_parse_E(parser);
    }
    else {
        printf("[SyntaxError] Unexpected token %s, expected TOKEN_PRINT or TOKEN_ID\n", temp_token->value);
        exit(1);
    }
    return NULL;    // epsilon
}

AST_T* parser_parse_stmt_list_prime(parser_T* parser)
{
    if (parser->token->type == TOKEN_SEMI) {
        parser_eat(parser, TOKEN_SEMI);
        AST_T* stmt = parser_parse_stmt(parser);
        AST_T* stmt_list_prime = parser_parse_stmt_list_prime(parser);

        return init_ast(NULL, stmt, stmt_list_prime);
    } 

    return NULL;
}

AST_T* parser_parse_print(parser_T* parser)
{
    
    token_T* print_token = parser_eat(parser, TOKEN_PRINT);

    if (parser->token->type != TOKEN_LPAREN) {
        printf("[SyntaxError] Missing `(` symbol after print. Parser expects `print(expr)`.\n");
        exit(1);
    }

    parser_eat(parser, TOKEN_LPAREN);
    AST_T* expr = parser_parse_E(parser);

    if (parser->token->type != TOKEN_RPAREN) {
        printf("[SyntaxError] Missing `)` symbol. Parser expects `print(expr)`\n");
        exit(1);
    }
    
    parser_eat(parser, TOKEN_RPAREN);
    return init_ast(print_token, NULL, expr);
}

AST_T* parser_parse_assignment(parser_T* parser)
{
    token_T* id_token = temp_token;     // the variable must come before `:=`
    parser_eat(parser, TOKEN_DEFINE);
    token_T* define_token = temp_token;
    AST_T* expr = parser_parse_E(parser);

    if (expr == NULL) {
        printf("[SyntaxError] Missing expression on the right hand side of assignment.\n");
        exit(1);
    }
    return init_ast(define_token, init_ast(id_token, NULL, NULL), expr);
}

AST_T* parser_parse_T(parser_T* parser)
{
    AST_T* factor = parser_parse_F(parser);
    AST_T* Tprime = parser_parse_Tprime(parser);

    /* If there is no Tprime, then just return F */
    if (Tprime == NULL)
        return factor;

    return init_ast(NULL, factor, Tprime);
}

AST_T* parser_parse_F(parser_T* parser)
{
    if (parser->token->type == TOKEN_ID) {
        token_T* id = parser_eat(parser, TOKEN_ID);
        return init_ast(id, NULL, NULL);
    } else if (parser->token->type == TOKEN_NUM) {
        token_T* num = parser_eat(parser, TOKEN_NUM);
        return init_ast(num, NULL, NULL);
    } else if (parser->token->type == TOKEN_LPAREN) {
        parser_eat(parser, TOKEN_LPAREN);
        AST_T* expr = parser_parse_E(parser);
        parser_eat(parser, TOKEN_RPAREN);
        return expr;
    }

    return NULL;
}

AST_T* parser_parse_Tprime(parser_T* parser)
{
    if (parser->token->type == TOKEN_MUL) {
        token_T* mul_token = parser_eat(parser, TOKEN_MUL);
        AST_T* F = parser_parse_F(parser);
        AST_T* Tprime = parser_parse_Tprime(parser);

        if (F == NULL) {
            printf("[SyntaxError] Missing operands near `*`. Expects expression like `a * b`.\n");
            exit(1);
        }

        return init_ast(mul_token, F, Tprime);
    } else if (parser->token->type == TOKEN_DIV) {
        token_T* div_token = parser_eat(parser, TOKEN_DIV);
        AST_T* F = parser_parse_F(parser);
        AST_T* Tprime = parser_parse_Tprime(parser);

        if (F == NULL) {
            printf("[SyntaxError] Missing operands near `/`. Expects expression like `a / b`.\n");
            exit(1);
        }

        return init_ast(div_token, F, Tprime);
    }

    return NULL;
}

AST_T* parser_parse_E(parser_T* parser)
{
    AST_T* T = parser_parse_T(parser);
    AST_T* Eprime = parser_parse_Eprime(parser);

    /* If there is no Eprime, then just return T */
    if (Eprime == NULL)
        return T;

    return init_ast(NULL, T, Eprime);
}

AST_T* parser_parse_Eprime(parser_T* parser)
{
    if (parser->token->type == TOKEN_ADD) {
        token_T* add_token = parser_eat(parser, TOKEN_ADD);
        AST_T* T = parser_parse_T(parser);
        AST_T* Eprime = parser_parse_Eprime(parser);

        if (T == NULL) {
            printf("[SyntaxError] Missing operands near `+`. Expects expression like `a + b`.\n");
            exit(1);
        }

        return init_ast(add_token, T, Eprime);
    } else if (parser->token->type == TOKEN_SUB) {
        token_T* sub_token = parser_eat(parser, TOKEN_SUB);
        AST_T* T = parser_parse_T(parser);
        AST_T* Eprime = parser_parse_Eprime(parser);

        if (T == NULL) {
            printf("[SyntaxError] Missing operands near `-`. Expects expression like `a - b`.\n");
            exit(1);
        }

        return init_ast(sub_token, T, Eprime);
    }

    return NULL;
}