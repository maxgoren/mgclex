#ifndef lex_h
#define lex_h
#ifdef __cplusplus
extern "C" {
#endif
#include "dfa/re2ast/src/ast.h"
#include "dfa/re2ast/src/parser.h"
#include "dfa/re_to_dfa.h"
#include "lex_token_def.h"

typedef struct {
    char* pattern;
    enum TKSymbol token;
} TokenRule;

typedef struct {
    char* pattern;
    int patlen;
    re_ast* ast;
    re_ast** node_table;
    int table_size;
} CombinedRE;

extern int num_rules;
extern bool in_string;
extern TokenRule rules[];
void tag_final_pos_with_token_id(re_ast* ast, int rulenum);
CombinedRE* combine(int numrules);
CombinedRE* init_lexer_patterns(int numrules);


#ifdef __cplusplus
}
#endif

#endif