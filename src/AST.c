#include "include/AST.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Initializes an AST node.
 */
AST_T* init_ast(token_T* token, AST_T* left, AST_T* right)
{
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->token = token;
    ast->left = left;
    ast->right = right;

    return ast;
}

/*
 * Frees the memory for an AST node.
 */
void free_ast(AST_T* root)
{
    if (root == NULL)
        return;

    free_ast(root->left);
    free_ast(root->right);
    free(root);
}