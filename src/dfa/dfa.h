#ifndef dfa_h
#define dfa_h
#include <stdlib.h>
#include <stdio.h>
#include "intset.h"
#include "dfastate.h"
#include "followpos.h"
#include "transition.h"
#include "re2ast/src/tokens.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    DFAState** states;
    int numstates;
} DFA;


void initDFA(DFA* dfa, int numstates);
void printDFA(DFA dfa);
void freeDFA(DFA* dfa);


#ifdef __cplusplus
}
#endif

#endif