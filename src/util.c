#include "util.h"

void dfsmat(Transition* t, int s, int mat[][256]) {
    if (t != NULL) {
        dfsmat(t->left,s,mat);
        mat[s][t->ch] = t->to;
        dfsmat(t->right,s,mat);
    }
}


void dfa2matrix(DFA* dfa, char* filename, char* symbols[], int num_symbols) {
    int matrix[dfa->numstates+1][256];
    for (int i = 0; i < dfa->numstates+1; i++)
        for (int j = 0; j < 256; j++)
            matrix[i][j] = 0;
    for (int i = 1; i <= dfa->numstates; i++) {
        dfsmat(dfa->states[i]->transitions, i, matrix);
    }
    FILE* fd = fopen(filename, "w+");
    fprintf(fd, "#ifndef lexer_matrix_h\n#define lexer_matrix_h\n\n");
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
    fprintf(fd, "int matrix[%d][256] = {\n", dfa->numstates+1);
    int i = 0;
    for (i = 0; i < dfa->numstates; i++) {
        fprintf(fd, "\t{ ");
        for (int j = 0; j < 255; j++) {
            fprintf(fd, "%d, ", matrix[i][j]);
        }
        fprintf(fd, "0},\n");
    }
    fprintf(fd, "\t{ ");
    for (int j = 0; j < 255; j++) {
        fprintf(fd, "%d, ", matrix[i][j]);
    }
    fprintf(fd, "0}\n");
    fprintf(fd, "};\n\n");
    fprintf(fd, "int accept[%d] = {\n", dfa->numstates+1);
    for (int i = 0; i <= dfa->numstates; i++) {
        if (dfa->states[i] != NULL && dfa->states[i]->is_accepting) {
            fprintf(fd, "\t%d", rules[dfa->states[i]->token_id].token);
        } else {
            fprintf(fd, "\t-1");
        }
        if (i < dfa->numstates) fprintf(fd,",\n");
    }
    fprintf(fd, "\n};\n\n#endif");
    fclose(fd);
}


void dfa2json(DFA* dfa) {
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

char *slurp_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(sizeof(char)*(file_size + 1));
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}