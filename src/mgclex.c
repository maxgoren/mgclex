#include <stdio.h>
#include <stdlib.h>
#include "lexgen.h"
#include "util.h"
#include "tokenrules.h"
#include "readconfig.h"
#define VERSION 1.0

void showUsage();
void generateLexer(char* specfilename, char* outfilename);

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
    generateLexer(argv[1], outfilename);
    return 0;
}

void generateLexer(char* specfile, char* outfile) {
    readConfig(specfile);
    printf("[*] Initializing...\n");
    CombinedRE* cre = init_lexer_patterns(num_rules);
    printf("[*] Compiling DFA...\n");
    DFA dfa = ast2dfa(cre->pattern, cre->ast, &cre->node_table);
    printf("[*] Writing matrix and accept states to %s\n", outfile);
    dfa2matrix(&dfa, outfile, symbols, num_symbols);
    printf("[*] Cleaning up...\n");
    freeDFA(&dfa);
    printf("[*] Complete!\n");
}

void showUsage() {
    printf("MGCLex v%f, The no-frills lexer generator.\n", VERSION);
    printf("Usage:\n");
    printf("\t mgclex <spec file name> <output file name>\n");
    printf("\n");
    printf("\n");
}
