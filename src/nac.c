#include "include/lexer.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h> // Include this for memory allocation functions

lexer_T* lexer_init_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* src = (char*)malloc(file_size + 1); // +1 for null terminator
    fread(src, 1, file_size, file);
    src[file_size] = '\0';

    fclose(file);

    return lexer_init(src);
}

int main() {
    lexer_T* lexer = lexer_init_from_file("examples/main.nac"); // Change the filename to your source code file

    token_T* token;
    while ((token = lexer_tokenize(lexer))->type != TOKEN_EOF) {
        // Process or print the token here as needed
        char* str = token_to_str(token);
        printf("%s\n", str);
        free(str);
    }

    // Clean up
    free(lexer->src);
    free(lexer);
    
    return 0;
}
