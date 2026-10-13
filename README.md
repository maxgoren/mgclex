# MGCLex

MGCLex is a lexical analyzer generator utilizing the Aho, Sethi, Ullman Direct DFA Construction to
quickly and painlessly generate a DFA based lexer for fast string tokenization.

## How To Use MGCLex

### Installing MGCLex

MGCLex can be built on linux/BSD using `make` by cloning this repository to your local machine and typing 
at the command line in the directory you cloned to:

      make && sudo make install && make clean

This will automatically build and install MGCLex.

### Spec Files 
 
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
      [^xyz] - Negated Character class, will match anyletter that _isnt_ xyz
      . - Wildcard to match any character, ex: r.n matches ran, and run, and rzn too, etc.
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

## Compressed & Un-compressed Tables

You have the choice two output two types of matrix, a raw uncompressed matrix
and a pair-compressed matrix which only stores valid transitions in a compressed format.

```
      mgclex <filename> [optional_output_filename] [-c]
```
The -c flag at the end is optional and can be used with or without a user defined output name,

so if you want to use the default output name  but still compress the table you would use
```
      mgclex <filename> -c
```
## Minimal State DFA

Though the dfa's created with aho, sethi, ullman direct-to-dfa algorithm are already pretty minimal, the -m flag
will do an additional step of running the DFA through a set partition refinement process (Moores Algorithm) to ensure
the resulting DFA has the minimal number of states. This can be used with both pair compressed and uncompressed matrixes, 
as the DFA is reduced before hand.

```
      mgclex <filename> [optional_output_filename] [-c] [-m]
```

