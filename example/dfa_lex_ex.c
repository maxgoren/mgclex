#include "../src/dfa/dfa.h"
#include "../src/lexgen.h"
typedef struct {
    int rule_id;
    int length;
    int lineno;
    char* text;
} TKToken;

typedef struct TKTokenListNode_ {
    TKToken* token;
    struct TKTokenListNode_* next;
} TKTokenListNode;

TKToken* makeTKToken(int rid, int len);
TKToken* nextToken(DFA* dfa, const char* input, re_ast** ast_node_table);
TKTokenListNode* makeTokenListNode(TKToken* token);
TKTokenListNode* lex_input(DFA* dfa, char* input, re_ast** ast_node_table);

//Classic Maximal-much: Prefer longest match, and equal length matches are chosen by priority
//with priority being order in the rule list.
TKToken* nextToken(DFA* dfa, const char* input, re_ast** ast_node_table) {
    int curr = 1;
    int last_accept = -1;
    int last_token_id = -1;
    int i = 0;
    for (; input[i] != '\0'; i++) {
        int next = -1;
#ifdef DEBUG
        printf("Current State: %d, Input Symbol: %c\n", dfa->states[curr]->label, input[i]);
#endif
        Transition* it = findTransition(dfa->states[curr]->transitions, input[i]);
        if (it != NULL) {
            if (input[i] == it->ch || ast_node_table[curr]->token.symbol == RE_PERIOD) {
                if (it->ch == '"') {
                    i++;
                    while (input[i] != '\0' && input[i] != '"')
                        i++;
                    if (input[i] != '"') {
                        printf("Unterminated string!\n");
                    } else {
                        i++;
                    }
                    return makeTKToken(36,i);
                } else {
                    next = it->to;
                }
            }
        } else if (ast_node_table[curr]->token.symbol == RE_PERIOD) {
            it = findTransition(dfa->states[curr]->transitions, '.');
            if (it != NULL)
                next = it->to;
        }    
        if (next == -1) {
            break;
        }
        curr = next;
        if (dfa->states[curr]->is_accepting) { 
            if (last_accept < i+1) {
                last_accept = i+1;
                last_token_id = dfa->states[curr]->token_id;
            } else {
                if (dfa->states[curr]->token_id < dfa->states[last_accept]->token_id) {
                    last_accept = i+1;
                    last_token_id = dfa->states[curr]->token_id;
                }
            }
        }
    }
    TKToken* t;
    if (last_accept == -1) {
        t = makeTKToken(-1, 0);
    } else {
        t = makeTKToken(last_token_id, last_accept);
    }
    return t;
}

bool in_string;
TKTokenListNode* lex_input(DFA* dfa, char* input, re_ast** ast_node_table) {
    char* p = input;
    TKTokenListNode dummy;
    TKTokenListNode* thead = &dummy; 
    in_string = false;
    int line_number = 0;
    while (*p != '\0') {
        // skip whitespace
        if (!in_string)
            while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
                if (*p == '\n') line_number++;
                p++;
            } 

        TKToken* t = nextToken(dfa, p, ast_node_table);
        if (t->rule_id == -1) {
            printf("Lex error near: %s\n", p);
            break;
        }
        t->lineno = line_number;
        thead->next = makeTokenListNode(t);
        thead = thead->next;
        int i, j;
        /*if (rules[t->rule_id].token == TK_STR) {
            for (i = 0, j = 1; j < t->length-1;)
                t->text[i++] = p[j++];
        } else {*/
        for (i = 0, j = 0; i < t->length;)
            t->text[i++] = p[j++];
        //}
        t->text[i++] = '\0';
        p += t->length;
    }
    thead->next = makeTokenListNode(makeTKToken(num_rules-1, 5));
    thead->next->token->text = "EOI";
#ifdef DEBUG
    for (TKTokenListNode* it = dummy.next; it != NULL; it = it->next) {
        printf("<%d, %s, %s> \n", rules[it->token->rule_id].token, rules[it->token->rule_id].pattern, it->token->text);
    }
#endif
    return dummy.next;
}

TKToken* makeTKToken(int rid, int len) {
    TKToken* tkt = malloc(sizeof(TKToken));
    tkt->rule_id = rid;
    tkt->length = len;
    tkt->lineno = 0;
    if (rid != -1 && len > 0) {
        tkt->text = malloc(sizeof(char)*(len+1));
    }
    return tkt;
}

TKTokenListNode* makeTokenListNode(TKToken* token) {
    TKTokenListNode* tn = malloc(sizeof(TKTokenListNode));
    tn->token = token;
    tn->next = NULL;
    return tn;
}