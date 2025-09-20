#include "dfa.h"

void initDFA(DFA* dfa, int numstates) {
    dfa->numstates = 0;
    dfa->states = malloc(sizeof(DFAState*)*numstates+1);
}

void printDFA(DFA dfa) {
    for (int i = 1; i <= dfa.numstates; i++) {
        printf("%d: ", i);
        printSet(dfa.states[i]->positions);
    }
    int mintc = 0, maxtc = 0, ttc = 0;
    for (int i = 1; i <= dfa.numstates; i++) {
        printf("%d: \n", i);
        int tc = printTransitions(dfa.states[i]->transitions, i);
        printf("\n");
        if (mintc == 0 || tc < mintc) mintc = tc;
        if (maxtc == 0 || tc > maxtc) maxtc = tc;
        ttc += tc;
        printf("\nTransition Count: %d\n", tc);
    }
    printf("Lowest transition count: %d\n", mintc);
    printf("Highest Trnaisiton count: %d\n", maxtc);
    printf("Num states: %d\n",dfa.numstates);
    printf("Total transitions: %d\n", ttc);
    printf("Possible Transitions: %d\n",(dfa.numstates+1)*128);
}

void freeDFA(DFA* dfa) {
    for (int i = 0; i <= dfa->numstates; i++) {
        if (dfa->states[i] != NULL) {
            freeDFAState(dfa->states[i]);
        }
    }
}

