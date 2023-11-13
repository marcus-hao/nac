#include "include/AST.h"
#include "include/lexer.h"
#include "include/nac.h"
#include "include/parser.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h> // Include this for memory allocation functions
#include <string.h>
#include <unistd.h>

char* read_file(const char* filename)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error reading file %s\n", filename);
        exit(1);
    }

    char* buffer = (char*) calloc(1, sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1) {
        buffer = (char*) realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);
    if (line)
        free(line);
    
    return buffer;
}

void compile(char* src)
{
    lexer_T* lexer = lexer_init(src);
    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse_program(parser);
    print_ast(root, 0);
    free(lexer);
    free_ast(root);
}

void compile_file(const char* filename)
{
    char* src = read_file(filename);
    compile(src);
    free(src);
}