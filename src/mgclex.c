#include <stdio.h>
#include <stdlib.h>
#include "../src/lexgen.h"
#include "../src/util.h"
#include "../src/lex_rules.h"

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
