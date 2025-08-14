#ifndef dfastate_h
#define dfastate_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "intset.h"
#include "transition.h"

typedef struct {
    int label;
    int token_id;
    bool is_accepting;
    int transition_count;
    Transition* transitions;
    Set* positions;
} DFAState;


void initDState(DFAState* state, int statenum);
DFAState* createState(int statenum, Set* positions);
void freeDFAState(DFAState* state);

#ifdef __cplusplus
}
#endif
#endif