#ifndef NAC_H
#define NAC_H

char* read_file(const char* filename);      /* Reads an input file */
void nac_lex(char * src);                   /* Demo for lexical analysis */
void compile(char* src);                    /* Performs lexical and syntax analysis */
void compile_file(const char* filename);    /* Performs lexical and syntax analysis of the file */

#endif