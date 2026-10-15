#include "tokenrules.h"

Vector* symbols;
Vector* rules;

void initSymbolSet() {
    symbols = (Vector*)malloc(sizeof(Vector));
    initVector(symbols);
}

void initTokenRulesVec() {
    rules = (Vector*)malloc(sizeof(Vector));
    initVector(rules);
}

int symbolExists(char* symbol) {
    for (int i = 0; i < symbols->n; i++) {
        if (strcmp(symbol, (char*)(symbols->data[i])) == 0)
            return i;
    }
    return -1;
}

int registerSymbol(char* symbol) {
    int symnum = -1;
    if ((symnum = symbolExists(symbol)) != -1)
        return symnum;
    addVec(symbols, strdup(symbol));
    return symbols->n-1;
}


void addTokenRule(char* pattern, int id) {
    TokenRule* rule = malloc(sizeof(TokenRule));
    rule->pattern = pattern;
    rule->token = id;
    addVec(rules, rule);
}

void freeTokenRule(TokenRule* tr) {
    free(tr->pattern);
    free(tr);
}