#include <stdio.h>
#include <stdlib.h>
#include "lexgen.h"
#include "util.h"
#include "tokenrules.h"
#include "readconfig.h"
#define MAJ_VERSION 1
#define MIN_VERSION 0

void showUsage();
void generateLexer(char* specfilename, char* outfilename, bool compressTables);

int main(int argc, char* argv[]) {
    char *outfilename;
    if (argc < 2) {
        showUsage();
        return -1;
    } else if (argc < 3) {
        outfilename = strdup("mgclex_matrix.h");
    } else {
        outfilename = argv[2];
    }
    generateLexer(argv[1], outfilename, argc == 4);
    return 0;
}


DFA minimize(DFA dfa) {
    //step 1, partition states into accepting and not accepting sets.
    Set accepting, notAccepting;
    initSet(&accepting, dfa.numstates);
    initSet(&notAccepting, dfa.numstates);
    for (int i = 1; i <= dfa.numstates; i++) {
        if (dfa.states[i]->is_accepting) {
            setAdd(&accepting, i);
        } else {
            setAdd(&notAccepting, i);
        }
    }
    
}

void generateLexer(char* specfile, char* outfile, bool compressTables) {
    printf("[*] Reading MGCLex configuration file...\n");
    readConfig(specfile);
    printf("[*] Initializing...\n");
    CombinedRE* cre = init_lexer_patterns(num_rules);
    printf("[*] Compiling DFA...\n");
    DFA dfa = ast2dfa(cre->pattern, cre->ast, &cre->node_table);
    /*if (compressTables) {
        dfa = minimize(dfa);
    }*/
    printf("[*] Writing matrix and accept states to %s\n", outfile);
    dfa2matrix(&dfa, outfile, symbols, num_symbols, 1);
    printf("[*] Cleaning up...\n");
    freeDFA(&dfa);
    printf("[*] Complete!\n");
}

void showUsage() {
    printf("MGCLex v%d.%d, The no-frills lexer generator. (c) 2025 MaxGCoding.com\n", MAJ_VERSION, MIN_VERSION);
    printf("Usage:\n");
    printf("\t mgclex <spec file name> [output file name]\n");
    printf("\n");
}
