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

void print_ast(AST_T* node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("*"); // Adjust the spacing for depth
    }

    if (node->token != NULL) {
        printf("%s\n", token_to_str(node->token));
    } else {
        printf("Non-terminal\n");
    }

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}