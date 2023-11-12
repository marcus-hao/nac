#ifndef AST_H
#define AST_H
#include "token.h"

typedef struct AST_STRUCT {
    token_T* token;
    struct AST_STRUCT* left;
    struct AST_STRUCT* right;
} AST_T;

AST_T* init_ast(token_T* token, AST_T* left, AST_T* right);

void print_ast(AST_T* node, int depth);

#endif