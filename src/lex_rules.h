#ifndef lex_spec_h
#define lex_spec_h
#ifdef __cplusplus
extern "C" {
#endif
#include "lex.h"
#include "lex_token_def.h"
//This file is used for specifying TokenRules
//TokenRules are a regex pattern, and an associated TKSymbol
//when DFA recognizes pattern, the TKSymbol is assigned 
//to the recognized strings

extern int num_rules;
extern TokenRule rules[];

#ifdef __cplusplus
}
#endif

#endif