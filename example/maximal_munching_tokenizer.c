#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer_matrix.h"
#include "../src/lex_token_def.h"
#include "../src/util.h"
char* token2string(int accept_state) {
    return symbolStr[accept[accept_state]];
}

typedef struct {
    enum TKSymbol symbol;
    char* text;
    int length;
} MyToken;

MyToken* makeLexToken(enum TKSymbol symbol, char* text, int length) {
    MyToken* tk = (MyToken*)malloc(sizeof(MyToken));
    tk->length = length;
    tk->text = (char*)malloc(sizeof(char)*(length+1));
    for (int i = 0; i < length; i++) {
        tk->text[i] = text[i];
    }
    tk->text[length] = '\0';
    tk->symbol = symbol;
    return tk;
}

MyToken* next_token(char* input) {
    int state = 1;
    int last_match = 0;
    int match_len = 0;
    for (char* p = input; *p; *p++) {
        if (matrix[state][*p] < 1) state = matrix[state]['.'];
        else state = matrix[state][*p];
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
        MyToken* next = next_token(input+i);
        if (next != NULL) {
            printf("<%s, %s>\n", symbolStr[next->symbol], next->text);
            i += next->length;
        } else {
            i++;
        }
    }
}

int main(int argc, char* argv[]) {
    tokenize_input(slurp_file(argv[1]));
    int farthest = 0;
    for (int i = 0; i < 175; i++) {
        bool run_start = false;
        for (int j = 0; j < 256; j++) {
            if (matrix[i][j] > 0 && run_start == false) {
                run_start = true;
            }
            if (matrix[i][j] > 0 && j > farthest) {
                farthest = j;
                printf(".");
            }
        }
    }
    printf(" %d\n", farthest);
}