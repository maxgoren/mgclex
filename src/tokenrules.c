#include "tokenrules.h"

int num_symbols;
int sym_cap;
char** symbols;

void initSymbolSet() {
    num_symbols = 0;
    sym_cap = 5;
    symbols = (char**)malloc(sizeof(char*)*sym_cap);
}

int registerSymbol(char* symbol) {
    for (int i = 0; i < num_symbols; i++) {
        if (strcmp(symbol, symbols[i]) == 0)
            return i;
    }
    if (num_symbols+1 == sym_cap) {
        char** tmp = symbols;
        symbols = (char**)malloc(sizeof(char*)*(2*sym_cap));
        for (int i = 0; i < num_symbols; i++)
            symbols[i] = tmp[i];
        sym_cap *= 2;
    }
    symbols[num_symbols++] = symbol;
    printf("Registered %s at %d\n", symbol, num_symbols);
    return num_symbols-1;
}

int num_rules;
int capacity;
TokenRule* rules;

void initTokenRulesVec() {
    num_rules = 0;
    capacity = 5;
    rules = (TokenRule*)malloc(sizeof(TokenRule)*capacity);
}

void addTokenRule(char* pattern, int id) {
    if (num_rules+1 == capacity) {
        TokenRule* tmp = rules;
        rules = (TokenRule*)malloc(sizeof(TokenRule)*(2*capacity));
        for (int i = 0; i < num_rules; i++) {
            rules[i].pattern = tmp[i].pattern;
            rules[i].token = tmp[i].token;
        }
        capacity *= 2;
        free(tmp);
    }
    rules[num_rules].pattern = pattern;
    rules[num_rules].token = id;
    num_rules++;
}
