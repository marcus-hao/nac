#ifndef TOKEN_H
#define TOKEN_H

/* Reserved Keywords*/
#define IF_KEYWORD "if"
#define PRINT_KEYWORD "print"

typedef struct TOKEN_STRUCT {
    char* value;
    enum {
        TOKEN_ID,
        TOKEN_NUM,
        TOKEN_IF,
        TOKEN_COMMA,
        TOKEN_NOTEQ,
        TOKEN_DEFINE,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_ADD,
        TOKEN_SUB,
        TOKEN_MUL,
        TOKEN_DIV,
        TOKEN_SEMI,
        TOKEN_PRINT,
        TOKEN_EOF
    } type;
} token_T;

token_T* init_token(char* value, int type);

const char* token_type_to_str(int type);

char* token_to_str(token_T* token);

#endif
