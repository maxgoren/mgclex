#ifndef lex_token_def_h
#define lex_token_def_h

enum TKSymbol {
    TK_NUMBER, TK_ID, TK_LP, TK_RP,
    TK_ASSIGN, TK_ADD, TK_SUB, 
    TK_MUL, TK_DIV, TK_SEMI, TK_PRINTLN,
    TK_EOI
};

extern char* symbolStr[];


#endif