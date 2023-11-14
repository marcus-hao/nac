#ifndef NAC_H
#define NAC_H

char* read_file(const char* filename);
void nac_lex(char * src);
void compile(char* src);
void compile_file(const char* filename);

#endif