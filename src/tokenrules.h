#ifndef lex_spec_h
#define lex_spec_h
#ifdef __cplusplus
extern "C" {
#endif
#include "lexgen.h"
#include "vector.h"

int registerSymbol(Vector* v, char* symbol);
void addTokenRule(Vector* v, char* pattern, int id);
void freeTokenRule(TokenRule* tr);

#ifdef __cplusplus
}
#endif

#endif