#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mgclex_matrix.h"

typedef struct Token_ {
    enum TKSymbol symbol;
    char* text;
    int length;
    struct Token_* next;
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

/* for use with pair compressed tables */
int get_next_compressed(int state, char p) {
    if (mgc_lexer_matrix[state]) {
        for (int i = 1; i < 2*mgc_lexer_matrix[state][0]; i += 2) {
            if (mgc_lexer_matrix[state][i] == p)
                return mgc_lexer_matrix[state][i+1];
        }
    }
    return 0;
}

/* for use with uncompressed matrix, O(1) lookup 
int get_next_fast(int state, char p) {
    return mgc_lex_matrix[state][p];
}
*/
Token* next_token(char* input) {
    int state = 1;
    int last_match = 0;
    int match_len = 0;
    for (char* p = input; *p; *p++) {
        state = get_next_compressed(state, *p);
        printf("%d -> ", state);
        if (state > 0 && mgc_lex_accept[state] > -1) {
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
    return makeLexToken(mgc_lex_accept[last_match], input, match_len);
}


Token* tokenize_input(char* input) {
    Token head; Token* list = &head;
    for (int i = 0; i < strlen(input);) {
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' || input[i] == '\n') i++;
        Token* next = next_token(input+i);
        if (next != NULL) {
            i += next->length;
            list->next = next;
	    list = next;
        } else {
            i++;
        }
    }
    return head.next;
}

void printTokens(Token* head) {
	for (Token* it = head; it != NULL; it = it->next) 
		printf("<%s, %s>\n", tokenStr[it->symbol], it->text);
}

int main(int argc, char* argv[]) {
    if (argc < 2)
       return 0;
    Token* tokens = tokenize_input(argv[1]);
    printTokens(tokens);
    return 0;
}
