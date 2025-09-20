mgclex:
	gcc -c src/dfa/re2ast/src/ast.c
	gcc -c src/dfa/re2ast/src/parser.c
	gcc -c src/dfa/re2ast/src/tokens.c 
	gcc -c src/dfa/build_dfa.c
	gcc -c src/dfa/dfa.c
	gcc -c src/dfa/dfastate.c
	gcc -c src/dfa/followpos.c
	gcc -c src/dfa/intset.c
	gcc -c src/dfa/ast_to_dfa.c
	gcc -c src/dfa/statequeue.c
	gcc -c src/dfa/transition.c
	gcc -c src/lexgen.c
	gcc -c src/tokenrules.c
	gcc -c src/util.c
	gcc -c src/readconfig.c
	gcc -c src/mgclex.c
	gcc *.o -o mgclex

install:
	cp ./mgclex /usr/local/bin/mgclex

clean:
	rm *.o
	rm mgclex