#ifndef mgclex_h
#define mgclex_h
#include <stdbool.h>

void showUsage();
void generateLexer(char* specfilename, char* outfilename, bool compressTables, bool mindfa);

#endif