#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenrules.h"
#include "readconfig.h"


char* extractPattern(char* str, int* pos) {
    char *pattern = (char*)malloc(sizeof(char)*255);
    int i = *pos, j = 0;
    if (str[i] == '"') i++;
    while (str[i]) {
        if (str[i] == '"' && str[i+1] == ',')
            break;
        pattern[j++] = str[i++];
    }
    if (str[i] == '"') i++;
    if (str[i] == ',') i++;
    *pos = i;
    return pattern;
}

char* extractSymbol(char* tmp, int pos) {
    char* tmp2 = malloc(sizeof(char)*strlen(tmp)); 
    int i = pos, j = 0;
    if (tmp[i] == ' ') i++;
    while (tmp[i] && tmp[i] != '}') { tmp2[j] = tmp[i]; i++; j++; }
    return tmp2;
}


void readConfig(char* filename) {
    char buffer[512];
    FILE* fd = fopen(filename, "r");
    if (fd != NULL) {
        initTokenRulesVec();
        initSymbolSet();
        while (fgets(buffer, sizeof(buffer), fd)) {
            int pos = 1;
            char *pat = extractPattern(buffer, &pos);
            printf("Pattern: %s\n", pat);
            char* symbol = extractSymbol(buffer, pos);
            printf("Symbol: %s\n", symbol);
            int id = registerSymbol(symbol);
            addTokenRule(pat, id);
            printf("\n-----------\n");
        }
        fclose(fd);
    } else {
        printf("Error: could not open specification file '%s' for reading.\n", filename);
        exit(EXIT_FAILURE);
    }
}
