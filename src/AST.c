#include "include/AST.h"
#include <stdio.h>
#include <stdlib.h>

AST_T* init_ast(token_T* token, AST_T* left, AST_T* right)
{
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->token = token;
    ast->left = left;
    ast->right = right;

    return ast;
}

void print_ast(AST_T* root, int depth)
{
    if (root != NULL) {
        if (root->token != NULL) {
            // Print node information
            printf("%*s%s: %s\n", depth * 2, "", token_type_to_str(root->token->type), root->token->value);
        } else {
            // Print non-terminal
            printf("%*sNon-terminal\n", depth * 2, "");
        }

        // Recursively print children nodes
        print_ast(root->left, depth + 1);
        print_ast(root->right, depth + 1);
    }
}

void free_ast(AST_T* root)
{
    if (root == NULL)
        return;

    free_ast(root->left);
    free_ast(root->right);
    free(root);
}

