#ifndef util_h
#define util_h
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexgen.h"

void dfa2matrix(DFA* d, char* filename, char* symbols[], int num_symbols);
void dfs(Transition* t, int s, int mat[][256]);
void dfstool(DFA* d, int matrix[][256]);

///experimental
void __dfa2json(DFA* d);
void serialize_dfa_state(DFAState* state, int from, FILE* fd);

#ifdef __cplusplus
}
#endif

#endif