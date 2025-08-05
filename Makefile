lex_example:
	gcc -c src/dfa/re2ast/src/ast.c
	gcc -c src/dfa/re2ast/src/parser.c
	gcc -c src/dfa/re2ast/src/tokens.c 
	gcc -c src/dfa/dfa.c
	gcc -c src/dfa/dfastate.c
	gcc -c src/dfa/followpos.c
	gcc -c src/dfa/intset.c
	gcc -c src/dfa/re_to_dfa.c
	gcc -c src/dfa/transition.c
	gcc -c src/lex.c
	gcc -c src/lex_token_def.c
	gcc -c src/util.c
	gcc -c example/ex.c
	gcc *.o -o ex
	rm *.o