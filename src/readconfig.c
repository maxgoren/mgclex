#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenrules.h"
#include "readconfig.h"

void skipWs(char* str, int* pos) {
    while (str[*pos] == ' ') *pos++;
}

char* extractPattern(char* str, int* pos) {
    char *pattern = (char*)malloc(sizeof(char)*255);
    int i = *pos, j = 0;
    if (str[i] == '"') i++;
    while (str[i]) {
        if (str[i] == '"' && str[i-1] != '\\' && str[i+1] == ',')
            break;
        pattern[j++] = str[i++];
    }
    if (str[i] == '"') i++;
    *pos = i;
    return pattern;
}

char* extractSymbol(char* tmp, int pos) {
    char* tmp2 = malloc(sizeof(char)*strlen(tmp)); 
    int i = pos, j = 0;
    if (tmp[i] == ' ') skipWs(tmp, &i);
    while (tmp[i] && tmp[i] != '}') { tmp2[j] = tmp[i]; i++; j++; }
    return tmp2;
}


void readConfig(char* filename) {
    char buffer[512];
    FILE* fd = fopen(filename, "r");
    if (fd != NULL) {
        initTokenRulesVec();
        initSymbolSet();
        int lineno = 0;
        while (fgets(buffer, sizeof(buffer), fd)) {
            int pos = 0;
            ++lineno;
            while (buffer[pos] && buffer[pos] != '{') pos++;
            if (buffer[pos] == '{') {
                pos++;
            } else {
                printf("Error: improperly formatted specification file on line %d.\n", lineno);
                exit(EXIT_FAILURE);
            }
            char *pat = extractPattern(buffer, &pos);
            printf("Pattern: %s\n", pat);
            if (buffer[pos] == ',') {
                pos++;
            } else {
                printf("Error: improperly formatted specification file on line %d.\n", lineno);
                exit(EXIT_FAILURE);
            }                                                                                                                                                                                                                   
            char* symbol = extractSymbol(buffer, pos);
            printf("Symbol: %s\n", symbol);
            int id = registerSymbol(symbol);
            addTokenRule(pat, id);
            printf("------------------------\n");
        }
        printf("Read: %d Rules for %d Symbols\n", num_rules, num_symbols);
        fclose(fd);
    } else {
        printf("Error: could not open specification file '%s' for reading.\n", filename);
        exit(EXIT_FAILURE);
    }
}
