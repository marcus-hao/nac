#include "include/AST.h"
#include <stdio.h>
#include <stdlib.h>

AST_T* init_ast(token_T* token, AST_T* left, AST_T* right, const char* label)
{
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->token = token;
    ast->left = left;
    ast->right = right;
    ast->label = label;

    return ast;
}

void print_ast(AST_T* ast, int level)
{
    if (ast == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        printf("--");
    }

    if (ast->label != NULL) {
        printf("%s\n", ast->label);
    }

    if (ast->token != NULL) {
        printf("%s: %s\n", token_type_to_str(ast->token->type), ast->token->value);
    } 
    
    if (ast->left != NULL)
        print_ast(ast->left, level + 1);

    if (ast->right != NULL)
        print_ast(ast->right, level + 1);
}

void free_ast(AST_T* root)
{
    if (root == NULL)
        return;

    free_ast(root->left);
    free_ast(root->right);
    free(root);
}