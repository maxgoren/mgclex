#ifndef build_dfa_h
#define build_dfa_h
#include "dfa.h"
#include "dfastate.h"

void initAlphabet(char* alphabet, char* re);
void addState(DFA* dfa, DFAState* state);
int nextStateNum(DFA* dfa);
Set* calculateNextStatesPositions(DFAState* curr_state, char input_symbol, re_ast** ast_node_table);
int findStateByPositions(DFA* dfa, Set* next_states);
int symbolIsInAlphabet(char* str, int n, char c);
DFA buildDFA(re_ast* ast, char* re, re_ast** ast_node_table);
DFAState* markAcceptState(DFAState* state, re_ast** ast_node_table);


#endif