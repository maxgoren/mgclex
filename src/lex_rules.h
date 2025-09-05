#ifndef lex_spec_h
#define lex_spec_h
#ifdef __cplusplus
extern "C" {
#endif
#include "lexgen.h"
//This file is used for specifying TokenRules
//TokenRules are a regex pattern, and an associated TKSymbol
//when DFA recognizes pattern, the TKSymbol is assigned 
//to the recognized strings
extern int num_symbols;
extern int sym_cap;
extern char** symbols;

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