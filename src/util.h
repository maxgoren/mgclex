#ifndef util_h
#define util_h
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexgen.h"

void dfa2matrix(DFA* d, char* filename, char* symbols[], int num_symbols, int asStr);
void dfs(Transition* t, int s, int mat[][256]);
void dfstool(DFA* d, int matrix[][256]);
void writeHeader(FILE* fd);
void writeFooter(FILE* fd);
void writeSymbolsAsStrings(FILE* fd, char* symbols[], int ns);
void writeEnum(FILE* fd, char* symbols[], int ns, int asStr);
void writeMatrix(FILE* fd, DFA* dfa, int matrix[][256]);
void writeAccept(FILE* fd, DFA* dfa);

#ifdef __cplusplus
}
#endif

#endif