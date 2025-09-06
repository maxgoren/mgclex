# MGCLex

MGCLex is a lexical analyzer generator utilizing 
the Aho, Sethi, Ullman Direct DFA Construction to
quickly and painlessly generate a DFA based lexer
for fast string tokenization.

## how to use mgclex
 
 mgclex expects a textfile containing patterns and symbols from which to build a dfa.
 each pair is on its own line, enclosed in braces:

      {"pattern",SYMBOL}

Patterns are specified as regular expressions.
Supported Regular expression operators:

      R|R - alternation
      R* - Occurs _zero_ or more times
      R+ - Occurs _one_ or more times
      R? - Occurs zero or one times
      RR - Concatenation
      [AEIOU] - Character classes, example matches a vowel
      [0-9A-Fa-f] - Ranges, example matches hexadecimal digits/chars
      . - Wildcard to match any character ex: ".*" is a pattern to match quoted strings.
      R(R*) - Grouping: Parentheses can be used to override operator precedence
      
To use any of the operators as literals, you must escape them with a \ (see calculator example).

For example if you wanted to tokenize expressions for a desk claculator app
your specification could look like this:

      {"[0-9]+(\.)?[0-9]*", TK_NUMBER}
      {"\+", TK_PLUS}
      {"-", TK_MINUS}
      {"\*", TK_MULT}
      {"/", TK_DIV}
      {"\(", TK_LPAREN}
      {"\)", TK_RPAREN}

Will output a header file, mylexer.h, which contains your DFA's transition matrix
and accept table. The file "matrix_lex_ex.c" in the example folder demonstrates using
the generated header to impelement a maximal-munch tokenizer.
