#include "tokenrules.h"


int symbolExists(Vector* symbols, char* symbol) {
    for (int i = 0; i < symbols->n; i++) {
        if (strcmp(symbol, (char*)(symbols->data[i])) == 0)
            return i;
    }
    return -1;
}

int registerSymbol(Vector* symbols, char* symbol) {
    int symnum = -1;
    if ((symnum = symbolExists(symbols, symbol)) != -1)
        return symnum;
    pushVector(symbols, strdup(symbol));
    return symbols->n-1;
}


void addTokenRule(Vector* rules, char* pattern, int id) {
    TokenRule* rule = malloc(sizeof(TokenRule));
    rule->pattern = pattern;
    rule->token = id;
    pushVector(rules, rule);
}

void freeTokenRule(TokenRule* tr) {
    free(tr->pattern);
    free(tr);
}