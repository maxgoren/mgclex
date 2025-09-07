#include "util.h"


//outputs DFA as a 2d matrix and accept table as a header file
void dfa2matrix(DFA* dfa, char* filename, char* symbols[], int num_symbols) {
    int matrix[dfa->numstates+1][256];
    dfstool(dfa, matrix);
    FILE* fd = fopen(filename, "w+");
    writeHeader(fd);
    writeEnum(fd, symbols, num_symbols);
    writeMatrix(fd, dfa, matrix);
    writeAccept(fd, dfa);
    writeFooter(fd);
    fclose(fd);
}


//Fills in matrix using dfa states transitions
void dfs(Transition* t, int s, int mat[][256]) {
    if (t != NULL) {
        dfs(t->left,s,mat);
        mat[s][t->ch] = t->to;
        dfs(t->right,s,mat);
    }
}

//Initialize matrix and call DFS on each states transitions
void dfstool(DFA* dfa, int matrix[][256]) {
    for (int i = 0; i < dfa->numstates+1; i++)
        for (int j = 0; j < 256; j++)
            matrix[i][j] = 0;
    for (int i = 1; i <= dfa->numstates; i++) {
        dfsmat(dfa->states[i]->transitions, i, matrix);
    }
}


void writeHeader(FILE* fd) {
    fprintf(fd, "#ifndef matrix_h\n");
    fprintf(fd, "#define matrix_h\n\n");
}

void writeFooter(FILE* fd) {
    fprintf(fd, "\n#endif");
}

void writeEnum(FILE* fd, char* symbols[], int num_symbols) {
    fprintf(fd, "enum TKSymbol {\n");
    int j = 0;
    while (j < num_symbols) {
        fprintf(fd, "%s", symbols[j]);
        if (j+1 < num_symbols) {
            fprintf(fd, ",");
            if (j % 5 == 0)
                fprintf(fd, "\n");
        }
        j++;
    }
    fprintf(fd, "\n};\n");
}

void writeMatrix(FILE* fd, DFA* dfa, int matrix[][256]) {
    fprintf(fd, "int matrix[%d][256] = {\n", dfa->numstates+1);
    int i = 0;
    for (i = 0; i <= dfa->numstates; i++) {
        fprintf(fd, "\t{ ");
        for (int j = 0; j < 255; j++) {
            fprintf(fd, "%d, ", matrix[i][j]);
        }
        if (i+1 == 256)
            fprintf(fd, "0}\n");
        else
            fprintf(fd, "0},\n");
        
    }
    fprintf(fd, "};\n\n");
}

void writeAccept(FILE* fd, DFA* dfa) {
    fprintf(fd, "int accept[%d] = {\n", dfa->numstates+1);
    for (int i = 0; i <= dfa->numstates; i++) {
        if (dfa->states[i] != NULL && dfa->states[i]->is_accepting) {
            fprintf(fd, "\t%d", rules[dfa->states[i]->token_id].token);
        } else {
            fprintf(fd, "\t-1");
        }
        if (i < dfa->numstates) fprintf(fd,",\n");
    }
    fprintf(fd, "\n};\n");
}




void __dfa2json(DFA* dfa) {
    FILE* fd = fopen("table_gen.trans", "w+");
    fprintf(fd, "{\n  \"DFA\": [\n");
    int i;
    for (i = 1; i < dfa->numstates; i++) {
        serialize_dfa_state(dfa->states[i], i, fd);
        fprintf(fd, ",\n");
    }
    serialize_dfa_state(dfa->states[i], i, fd);
    fprintf(fd, "\n\t]\n}\n");
    fclose(fd);
}

void serialize_dfa_state(DFAState* state, int from, FILE* fd) {
    if (state == NULL)
        return;
    Transition* st[255];
    int stsp = 0;
    int tc = 0;
    fprintf(fd, "\t\t{\n\t\t\t\"state\": %d,\n\t\t\t\"accepting\": %s,\n\t\t\t\"transitions\":  [", from, state->is_accepting ? "true":"false");
    Transition* it = state->transitions;
    while (it != NULL) {
        st[++stsp] = it;
        it = it->left;
    }
    if (stsp > 0) fprintf(fd, "\n");
    while (stsp > 0) {
        it = st[stsp--];
        if (it != NULL) {
            fprintf(fd, "\t\t\t\t{ \"symbol\": \"%c\", \"destination\": %d }", it->ch, it->to);
            tc++;
            it = it->right;
            while (it != NULL) {
                st[++stsp] = it;
                it = it->left;
            }
        }
        if (stsp > 0) fprintf(fd, ",\n");
    }
    fprintf(fd, " ]\n\t\t}");
}
