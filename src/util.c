#include "util.h"


//outputs DFA as a 2d matrix and accept table as a header file
void dfa2matrix(DFA* dfa, char* filename, char* symbols[], int num_symbols) {
    int matrix[dfa->numstates+1][256];
    dfstool(dfa, matrix);
    FILE* fd = fopen(filename, "w+");
    if (fd != NULL) {
        writeHeader(fd);
        writeEnum(fd, symbols, num_symbols);
        writeMatrix(fd, dfa, matrix);
        writeAccept(fd, dfa);
        writeFooter(fd);
        fclose(fd);
    } else {
        printf("Error: couldn't open '%s' for writing", filename);
        exit(EXIT_FAILURE);
    }
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
        dfs(dfa->states[i]->transitions, i, matrix);
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