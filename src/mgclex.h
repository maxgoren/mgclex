#ifndef mgclex_h
#define mgclex_h
#include <stdbool.h>

typedef struct {
    char** symbols;
    int num_symbols;
} TerminalList;

void showUsage();
TerminalList* generateLexer(char* specfilename, char* outfilename, bool compressTables, bool mindfa, int loud);

#endif