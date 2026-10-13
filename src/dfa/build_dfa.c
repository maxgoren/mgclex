#include "build_dfa.h"
#include "statequeue.h"

void addState(DFA* dfa, DFAState* state) {
    dfa->states[state->label] = state;
}

bool findInCharClass(char* ccl, char input_symbol) {
    for (char *sp = ccl; *sp; sp++) {
        if (*sp == input_symbol)
            return true;
    }
    return false;
}

bool findInputSymbol(int t, char input_symbol, re_ast** ast_node_table) {
    if (ast_node_table[t]->token.symbol == RE_CCL) {
        if (findInCharClass(ast_node_table[t]->token.ccl, input_symbol)) {
            return true;
        }
    } else {
        if (ast_node_table[t]->token.ch == input_symbol || ast_node_table[t]->token.symbol == RE_PERIOD)
            return true;
    }
    return false;
}


Set* calculateNextStatesPositions(DFAState* curr_state, char input_symbol, re_ast** ast_node_table) {
    Set* next_states = createSet(nonleaves+1);
    for (int i = 0; i < curr_state->positions->n; i++) {
        int t = curr_state->positions->members[i];
        if (findInputSymbol(t, input_symbol, ast_node_table)) {
            next_states = setUnion(next_states, ast_node_table[t]->followpos);
        }
    }
    return next_states;
}

int findStateByPositions(DFA* dfa, Set* next_states) {
    for (int i = 1; i <= dfa->numstates; i++) {
        if (setsEqual(next_states, dfa->states[i]->positions)) {
            return i;
        }
    }
    return -1;
}

int nextStateNum(DFA* dfa) {
    return ++dfa->numstates;
}

DFA buildDFA(re_ast* ast, char* re, re_ast** ast_node_table) {
    int found;
    int max_table_size = (strlen(re)+5);
    char* alphabet = malloc(sizeof(char)*max_table_size); 
    if (alphabet == NULL) {
        printf("Malloc failed :(\n");
        exit(EXIT_FAILURE);
    }
    DFA dfa;
    StateQueue fq;
    initAlphabet(alphabet, re);
    initDFA(&dfa,numleaves+1, alphabet);
    addState(&dfa, createState(nextStateNum(&dfa), copySet(ast->firstpos)));
    initQueue(&fq);
    enQueue(&fq,  dfa.states[1]);
    while (!emptyQueue(&fq)) {
        DFAState* curr_state = deQueue(&fq);
        for (char *input_symbol = alphabet; *input_symbol; input_symbol++) {
#ifdef DEBUG
            printf("Input Symbol: %c\n", *input_symbol);
#endif
            Set* next_states = calculateNextStatesPositions(curr_state, *input_symbol, ast_node_table);
            if (!isSetEmpty(next_states)) {
                if ((found = findStateByPositions(&dfa, next_states)) > -1) {
                    curr_state->transitions = addTransition(curr_state->transitions, dfa.states[found]->label, *input_symbol);
                    curr_state->transition_count += 1;
                    freeSet(next_states);
#ifdef DEBUG                    
                    printf("State Already Exists, Adding Transition:  %d - (%c) - %d\n", curr_state->label, *input_symbol, dfa.states[found]->label);
#endif
                } else {
                    DFAState* new_state = createState(nextStateNum(&dfa), copySet(next_states)); 
                    addState(&dfa, new_state);
                    curr_state->transitions = addTransition(curr_state->transitions, new_state->label, *input_symbol);
                    curr_state->transition_count += 1;
                    enQueue(&fq, new_state);
#ifdef DEBUG
                    printf("Adding new state: %d, Transition: %d - (%c) - %d\n", new_state->label, curr_state->label, *input_symbol, new_state->label);
#endif
                }
            } else {
                free(next_states);
            }
        }
    }
    for (int i = 1; i <= dfa.numstates; i++) {
        dfa.states[i] = markAcceptState(dfa.states[i], ast_node_table);
    }
    return dfa;
}

DFAState* markAcceptState(DFAState* next_state, re_ast** ast_node_table) {
    for (int j = 0; j < next_state->positions->n; j++) {
        int pos = next_state->positions->members[j];
        if (ast_node_table[pos]->token.ch == '#')  {      
            next_state->is_accepting = true; 
            int leaf_id = ast_node_table[pos]->tk_token_id;
            if (next_state->token_id == -1 || leaf_id < next_state->token_id) {
                next_state->token_id = leaf_id;
            }
        }
    }
    return next_state;
}


int symbolIsInAlphabet(char* str, int n, char c) {
    for (int i = 0; i < n; i++) {
        if (str[i] == c)
            return i;
    }
    return -1;
}


void initAlphabet(char* alphabet,  char* re) {
    int k = 0, p = 0;
#ifdef DEBUG
    printf("Getting alphabet from %s\n", re);
#endif
    for (int i = 0; re[i]; i++) {
        if (re[i] != '#' && (is_char(re[i]) || is_digit(re[i]) || is_special(re[i])) && symbolIsInAlphabet(alphabet, k, re[i]) == -1)
            alphabet[k++] = re[i];
    }
#ifdef DEBUG
    printf("Alphabet: %s \n", alphabet);
#endif
}

int map_old_dest(Set* groups[], int numgroups, int old) {
    for (int i = 0; i < numgroups; i++) {
        int t = setContains(groups[i], old);
        if (t != -1)
            return i;
    }
    return -1;
}
DFA minimize(DFA dfa, re_ast** ast_node_table) {
    Set* groups[512];
    int numgroups = 0;
    char* alphabet = dfa.alphabet;
    
    groups[0] = createSet(255);
    numgroups = 1;
    
    int token_to_group[512];
    int in_group[512];
    for (int i = 0; i < 512; i++) { 
        token_to_group[i] = -1;
        in_group[i] = -1;
    }
    
    // partitioning based on token_id
    for (int i = 1; i <= dfa.numstates; i++) {
        int tid = dfa.states[i]->token_id;
        if (tid == -1) {
            setAdd(groups[0], i);
            in_group[i] = 0;
        } else {
            if (token_to_group[tid] == -1) {
                groups[numgroups] = createSet(255);
                token_to_group[tid] = numgroups;
                numgroups++;
            }
            int target_group = token_to_group[tid];
            setAdd(groups[target_group], i);
            in_group[i] = target_group;
        }
    }
    
    bool did_change = false;
    do {
        did_change = false;
        int current_limit = numgroups;
        
        for (int i = 0; i < current_limit; i++) {
            if (groups[i]->n < 2) continue; // singletons cannot be split
            
            Set* newgroup = createSet(255);
            int first = groups[i]->members[0];
            int next = groups[i]->members[1];
            int spt = 2;
            
            while (next != 0) {
                bool split_element = false;
                for (int j = 0; alphabet[j]; j++) {
                    Transition* ftr = findTransition(dfa.states[first]->transitions, alphabet[j]);
                    Transition* gtr = findTransition(dfa.states[next]->transitions, alphabet[j]);
                    int fg = (ftr != NULL) ? in_group[ftr->to] : -1;
                    int ng = (gtr != NULL) ? in_group[gtr->to] : -1;
                    
                    if (fg != ng) {
                        split_element = true;
                        break; 
                    }
                }
                
                if (split_element) {
                    setAdd(newgroup, next);
                }
                
                next = (spt < groups[i]->n) ? groups[i]->members[spt++] : 0;
            }
            
            if (!isSetEmpty(newgroup)) {
                for (int t = 0; t < newgroup->n; t++) {
                    int state_to_move = newgroup->members[t];
                    setErase(groups[i], state_to_move);
                    in_group[state_to_move] = numgroups;
                }
                groups[numgroups] = newgroup;
                numgroups++;
                did_change = true;
            }
        }
    } while (did_change);
    
    DFA result;
    initDFA(&result, numgroups + 1, alphabet);
    
    for (int g = 0; g < numgroups; g++) {
        Set* positions = createSet(255);
        for (int m = 0; m < groups[g]->n; m++) {
            positions = setUnion(positions, dfa.states[groups[g]->members[m]]->positions);
        }
        result.states[g + 1] = createState(g + 1, positions);
        result.numstates++;
    }
    
    // Reconstruct Transitions
    for (int i = 0; i < numgroups; i++) {
        if (groups[i]->n == 0) continue;
        int rep = groups[i]->members[0];
        for (int j = 0; alphabet[j]; j++) {
            Transition* tt = findTransition(dfa.states[rep]->transitions, alphabet[j]);
            if (tt != NULL) {
                int ndst = in_group[tt->to];
                if (ndst >= 0) {
                    result.states[i + 1]->transitions = addTransition(result.states[i + 1]->transitions, result.states[ndst + 1]->label, tt->ch);
                }
            }
        }
    }
    
    // Reconstruct Token Mapping
    for (int i = 0; i < numgroups; i++) {
        result.states[i + 1]->is_accepting = false;
        result.states[i + 1]->token_id = -1;
        for (int j = 0; j < groups[i]->n; j++) {
            int old_state_id = groups[i]->members[j];
            if (dfa.states[old_state_id]->is_accepting) {
                if (!result.states[i + 1]->is_accepting) {
                    result.states[i + 1]->is_accepting = true;
                    result.states[i + 1]->token_id = dfa.states[old_state_id]->token_id;
                } else {
                    if (dfa.states[old_state_id]->token_id < result.states[i + 1]->token_id) {
                        result.states[i + 1]->token_id = dfa.states[old_state_id]->token_id;
                    }
                }
            }
        }
    }
    
    return result;
}
