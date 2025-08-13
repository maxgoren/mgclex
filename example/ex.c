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
    /*TKTokenListNode* token_list = lex_input(&dfa, slurp_file(argv[1]), cre->node_table);
    for (TKTokenListNode* it = token_list; it != NULL; it = it->next) {
        printf("<%s, %s>\n", symbolStr[rules[it->token->rule_id].token], it->token->text);
    }*/
    dfa2matrix(&dfa, "lexer_matrix.h");
}