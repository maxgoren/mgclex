#include "lex_rules.h"

int num_rules = 13;

TokenRule rules[] = {
    {"(\\d+)[\\.](\\d+)",TK_NUMBER},
    {"[0-9]+", TK_NUMBER},
    {"println", TK_PRINTLN},
    {"[A-Za-z][A-Za-z0-9_]*", TK_ID},
    {"\\(", TK_LP},
    {"\\)", TK_RP},
    {"\\+", TK_ADD},
    {"-", TK_SUB},
    {"\\*", TK_MUL},
    {"/", TK_DIV},
    {":=", TK_ASSIGN},
    {";", TK_SEMI},
    {"<fin.>", TK_EOI}
};