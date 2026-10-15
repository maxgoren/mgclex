#ifndef lex_h
#define lex_h
#ifdef __cplusplus
extern "C" {
#endif
#include "dfa/re2ast/src/ast.h"
#include "dfa/re2ast/src/parser.h"
#include "dfa/ast_to_dfa.h"
#include "vector.h"

typedef struct {
    char* pattern;
    int token;
} TokenRule;

typedef struct {
    char* pattern;
    int patlen;
    re_ast* ast;
    re_ast** node_table;
    int table_size;
} CombinedRE;

typedef struct {
    int num_rules;
    TokenRule* rules;
} RuleSet;

extern Vector* rules;
void tag_final_pos_with_token_id(re_ast* ast, int rulenum);
CombinedRE* combine(int numrules);
CombinedRE* init_lexer_patterns(int numrules);


#ifdef __cplusplus
}
#endif

#endif