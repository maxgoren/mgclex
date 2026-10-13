#include <stdio.h>
#include <stdlib.h>
#include "lexgen.h"
#include "util.h"
#include "tokenrules.h"
#include "readconfig.h"
#define MAJ_VERSION 1
#define MIN_VERSION 2

void showUsage();
void generateLexer(char* specfilename, char* outfilename, bool compressTables, bool mindfa);

int main(int argc, char* argv[]) {
    char *outfilename;
    bool compressTable = false, minDFA = false;
    if (argc < 2) {
        showUsage();
        return -1;
    } else if (argc < 3) {
        outfilename = strdup("mgclex_matrix.h");
    } else {
        if (argv[2][0] != '-') {
            outfilename = argv[2];
        } else {
            outfilename = strdup("mgclex_matrix.h");
        }
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {
                if (argv[i][j] == 'c') compressTable = true;
                if (argv[i][j] == 'm') minDFA = true;
            }
        }
    }
    generateLexer(argv[1], outfilename, compressTable, minDFA);
    return 0;
}


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
