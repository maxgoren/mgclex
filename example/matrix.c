#include <stdio.h>
#include "../lexer_matrix.h"
#include "../src/lex_token_def.h"

int find(char* input) {
    int state = 1;
    for (char* p = input; *p; *p++) {
        state = matrix[state][*p];
        printf("%d -> ", state);
    }
    printf("fin.\n");
    return state;
}

int main(int argc, char* argv[]) {
    int d = find(argv[1]);
    printf("%d, %s\n", d, symbolStr[accept[d]]);
}