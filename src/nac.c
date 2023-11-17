#include "include/AST.h"
#include "include/lexer.h"
#include "include/nac.h"
#include "include/parser.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Reads the input file and returns a character buffer.
 */
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

/*
 * Performs lexical analysis to print the sequence of tokens.
 *
 * This function is only used for demo purposes.
 */
void nac_lex(char * src)
{
    printf("\nPerforming lexical analysis\n");
    printf("---------------------------\n");
    
    lexer_T* lexer = lexer_init(src);

    token_T* token;
    while ((token = lexer_tokenize(lexer))->type != TOKEN_EOF) {
        char* str = token_to_str(token);
        printf("%s\n", str);
        free(str);
    }
    free(lexer);
}

/*
 * Performs lexical and syntax analysis of the source code.
 * 
 * This function is called by `compile_file`.
 */
void compile(char* src)
{
    lexer_T* lexer = lexer_init(src);
    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse_program(parser);
    printf("Program parsed successfully!\n");
    free(lexer);
    free_ast(root);
}

/*
 * Performs lexical and syntax analysis of the input file.
 * 
 * This function calls `compile`.
 */
void compile_file(const char* filename)
{
    char* src = read_file(filename);
    printf("\nThe program to parse is the following:\n");
    printf("%s\n", src);
    /* For demo, we show how the lexer performs tokenization. */
    nac_lex(src);
    compile(src);
    free(src);
}