#ifndef lex_spec_h
#define lex_spec_h
#ifdef __cplusplus
extern "C" {
#endif
#include "lexgen.h"
#include "vector.h"


extern Vector* symbols;
extern Vector* rules;

void initSymbolSet();
void initTokenRulesVec();
int registerSymbol(char* symbol);
void addTokenRule(char* pattern, int id);
void freeTokenRule(TokenRule* tr);

#ifdef __cplusplus
}
#endif

#endif