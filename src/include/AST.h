#ifndef AST_H
#define AST_H
#include "token.h"

typedef struct AST_STRUCT {
    token_T* token;             /* The token */
    struct AST_STRUCT* left;    /* The left node */
    struct AST_STRUCT* right;   /* The right node */
} AST_T;

AST_T* init_ast(token_T* token, AST_T* left, AST_T* right);     /* Initializes an AST node */

void free_ast(AST_T* root);                 /* Frees the memory for an AST node */

void print_ast(AST_T* root, int depth);     /* Prints the AST */

void print_tree(AST_T* node);

#endif