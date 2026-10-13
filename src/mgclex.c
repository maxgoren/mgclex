#include <stdio.h>
#include <stdlib.h>
#include "lexgen.h"
#include "util.h"
#include "tokenrules.h"
#include "readconfig.h"
#include "mgclex.h"
#define MAJ_VERSION 1
#define MIN_VERSION 2

void generateLexer(char* specfile, char* outfile, bool compressTables, bool minDFA) {
    printf("[*] Reading MGCLex configuration file...\n");
    readConfig(specfile);
    printf("[*] Initializing...\n");
    CombinedRE* cre = init_lexer_patterns(num_rules);
    printf("[*] Compiling DFA...\n");
    DFA dfa = ast2dfa(cre->pattern, cre->ast, &cre->node_table, minDFA);
    printf("[*] Writing matrix and accept states to %s\n", outfile);
    dfa2matrix(&dfa, outfile, symbols, num_symbols, 1, compressTables);
    printf("[*] Cleaning up...\n");
    freeDFA(&dfa);
    printf("[*] Complete!\n");
}

void showUsage() {
    printf("MGCLex v%d.%d, The no-frills lexer generator. (c) 2026 MaxGCoding.com\n", MAJ_VERSION, MIN_VERSION);
    printf("Usage:\n");
    printf("\t mgclex <spec file name> [output file name] [options]\n");
    printf("\t Options: \n \t \t -c pair compress tables\n \t \t -m minimize resultant DFA (Moores Algorithm)\n");
    printf("\n");
}
