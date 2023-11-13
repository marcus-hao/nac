#ifndef AST_H
#define AST_H
#include "token.h"

typedef struct AST_STRUCT {
    token_T* token;
    struct AST_STRUCT* left;
    struct AST_STRUCT* right;
    const char* label;
} AST_T;

AST_T* init_ast(token_T* token, AST_T* left, AST_T* right, const char* label);

void free_ast(AST_T* root);

void print_ast(AST_T* ast, int level);

void print_tree(AST_T* node);

#endif