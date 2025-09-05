#include <stdio.h>
#include <stdlib.h>
#include "lexgen.h"
#include "util.h"
#include "lex_rules.h"
#include "readconfig.h"

int main(int argc, char* argv[]) {
    char *filename;
    if (argc < 3) {
        filename = strdup("mgclex_matrix.h");
    } else {
        filename = argv[2];
    }
    readConfig(argv[1]);
    printf("[*] Initializing...\n");
    CombinedRE* cre = init_lexer_patterns(num_rules);
    printf("[*] Compiling DFA...\n");
    DFA dfa = ast2dfa(cre->pattern, cre->ast, &cre->node_table);
    printf("[*] Writing matrix and accept states to %s\n", filename);
    dfa2matrix(&dfa, filename, symbols, num_symbols);
    printf("[*] Cleaning up...\n");
    freeDFA(&dfa);
    printf("[*] Complete!\n");
    return 0;
}
