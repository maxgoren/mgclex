#include <stdio.h>
#include <stdlib.h>
#include "lexgen.h"
#include "util.h"
#include "tokenrules.h"
#include "readconfig.h"
#include "mgclex.h"
#define MAJ_VERSION 1
#define MIN_VERSION 2

TerminalList* generateLexer(char* specfile, char* outfile, bool compressTables, bool minDFA, int loud) {
    printf("[*] Reading MGCLex configuration file...\n");
    Vector* rules = allocVector();
    Vector* symbols = allocVector();
    readConfig(specfile, rules, symbols, loud);
    printf("[*] Initializing...\n");
    CombinedRE* cre = init_lexer_patterns(rules);
    TerminalList* tl = malloc(sizeof(TerminalList));
    tl->symbols = (char**)symbols->data;
    tl->num_symbols = symbols->n;
    printf("[*] Compiling DFA...\n");
    DFA dfa = ast2dfa(cre->pattern, cre->ast, &cre->node_table, minDFA);
    printf("[*] Writing matrix and accept states to %s\n", outfile);
    dfa2matrix(&dfa, outfile, rules, symbols, 1, compressTables);
    printf("[*] Cleaning up...\n");
    freeDFA(&dfa);
    for (int i = 0; i < rules->n; i++) {
        freeTokenRule((TokenRule*)rules->data[i]);
    }
    freeVector(rules);
    free(symbols);
    printf("[*] Complete!\n");
    return tl;
}

void showUsage() {
    printf("MGCLex v%d.%d, The no-frills lexer generator. (c) 2026 MaxGCoding.com\n", MAJ_VERSION, MIN_VERSION);
    printf("Usage:\n");
    printf("\t mgclex <spec file name> [output file name] [options]\n");
    printf("\t Options: \n \t \t -v verbose output \n \t \t -c pair compress tables\n \t \t -m minimize resultant DFA (Moores Algorithm)\n");
    printf("\n");
}
