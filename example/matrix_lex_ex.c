#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mgclex_matrix.h"

typedef struct {
    enum TKSymbol symbol;
    char* text;
    int length;
} Token;

Token* makeLexToken(enum TKSymbol symbol, char* text, int length) {
    Token* tk = (Token*)malloc(sizeof(Token));
    tk->length = length;
    tk->text = (char*)malloc(sizeof(char)*(length+1));
    for (int i = 0; i < length; i++) {
        tk->text[i] = text[i];
    }
    tk->text[length] = '\0';
    tk->symbol = symbol;
    return tk;
}

Token* next_token(char* input) {
    int state = 1;
    int last_match = 0;
    int match_len = 0;
    for (char* p = input; *p; *p++) {
        state = matrix[state][*p];
        printf("%d -> ", state);
        if (state > 0 && accept[state] > -1) {
            last_match = state;
            match_len = (p-input)+1;
        }
        if (state < 1) {
            break;
        }
    }
    printf("\n");
    if (last_match == 0) {
        return NULL;
    }
    return makeLexToken(accept[last_match], input, match_len);
}


void tokenize_input(char* input) {
    for (int i = 0; i < strlen(input);) {
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' || input[i] == '\n') i++;
        Token* next = next_token(input+i);
        if (next != NULL) {
            printf("<%s, %s>\n", symbolStr[next->symbol], next->text);
            i += next->length;
        } else {
            i++;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2)
       return 0;
    tokenize_input(argv[1]);
    return 0;
}
