# MGCLex

MGCLex is a lexical analyzer generator utilizing 
the Aho, Sethi, Ullman Direct DFA Construction to
quickly and painlessly generate a DFA based lexer
for fast string tokenization.

## how to use mgclex
 
There are two (2) possible ways to use mgclex in your project.

    1) use mgclex to generate the transition and accepting state
       tables as a header file for you to use as the basis of your own 
       tokenization system, this is the most flexible method and the "quickest"
       way of getting your project up and running.

    OR

    2) use the DFA structure and its Transition AVL trees directly along with the ast_node_table
       as the basis for your pattern matching needs. This is the method of choice for those who want
       the finest degree of control over.

Regardless of whether you choose method 1 or 2, there are a few steps you need to take for both:

    1) in lex_token_def.h there is a "TKSymbol" enum. Each TKSymbol will be used for identifying
       what a recognized lexeme is. As an example, we might use TK_NUMBER for tagging a lexeme 
       comprised of all numerical digits

    2) in lex_rules.h we specify the regular expression patterns used to match each
        symbol declared in the TKSymbol enum to a lexeme appearing in the input

 Once this is complete running:

	make && mgclex mylexer.h

Will output a header file, mylexer.h, which contains your DFA's transition matrix
and accept table. The file "matrix_lex_ex.c" in the example folder demonstrates using
the generated header to impelement a maximal-munch tokenizer.
