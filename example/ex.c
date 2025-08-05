#include <stdio.h>
#include <stdlib.h>
#include "../src/lex.h"
#include "../src/lex_rules.h"
#include "../src/util.h"
//required to construct DFA, 

DFA dfa;

int main(int argc, char* argv[]) {
    CombinedRE* cre = init_lexer_patterns(num_rules-1);
    dfa = ast2dfa(cre->pattern, cre->ast, &cre->node_table);
    char* input = "def fib(var x) { if (x < 2) { return 1; } return fib(x-1)+fib(x-2); }";
    TKTokenListNode* token_list = lex_input(&dfa, input, cre->node_table);
    for (TKTokenListNode* it = token_list; it != NULL; it = it->next) {
        printf("<%s, %s>\n", symbolStr[rules[it->token->rule_id].token], it->token->text);
    }
    dfa2matrix(&dfa, "lexer_matrix.h");
}