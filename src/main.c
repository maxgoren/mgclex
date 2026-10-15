#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mgclex.h"

int main(int argc, char* argv[]) {
    char *outfilename;
    bool compressTable = false, minDFA = false;
    int loud = 0;
    if (argc < 2) {
        showUsage();
        return -1;
    } else if (argc < 3) {
        outfilename = strdup("mgclex_matrix.h");
    } else {
        if (argv[2][0] != '-') {
            outfilename = argv[2];
        } else {
            outfilename = strdup("mgclex_matrix.h");
        }
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {
                if (argv[i][j] == 'c') compressTable = true;
                if (argv[i][j] == 'm') minDFA = true;
                if (argv[i][j] == 'v') loud = 1;
            }
        }
    }
    generateLexer(argv[1], outfilename, compressTable, minDFA, loud);
    return 0;
}