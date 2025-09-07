#ifndef lex_spec_h
#define lex_spec_h
#ifdef __cplusplus
extern "C" {
#endif
#include "lexgen.h"

//For creating Symbol enum
extern int num_symbols;
extern int sym_cap;
extern char** symbols;

//For holding pattern/symbol pairs in memory
extern int capacity;
extern int num_rules;
extern TokenRule* rules;

void initSymbolSet();

void initTokenRulesVec();
int registerSymbol(char* symbol);
void addTokenRule(char* pattern, int id);

#ifdef __cplusplus
}
#endif

#endif