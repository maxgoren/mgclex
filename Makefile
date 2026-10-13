mgclex:
	gcc -c -fPIC src/dfa/re2ast/src/ast.c
	gcc -c -fPIC src/dfa/re2ast/src/parser.c
	gcc -c -fPIC src/dfa/re2ast/src/tokens.c 
	gcc -c -fPIC src/dfa/build_dfa.c
	gcc -c -fPIC src/dfa/dfa.c
	gcc -c -fPIC src/dfa/dfastate.c
	gcc -c -fPIC src/dfa/followpos.c
	gcc -c -fPIC src/dfa/intset.c
	gcc -c -fPIC src/dfa/ast_to_dfa.c
	gcc -c -fPIC src/dfa/statequeue.c
	gcc -c -fPIC src/dfa/transition.c
	gcc -c -fPIC src/lexgen.c
	gcc -c -fPIC src/tokenrules.c
	gcc -c -fPIC src/util.c
	gcc -c -fPIC src/readconfig.c
	gcc -c -fPIC src/mgclex.c
	gcc -shared -o libmgclex.so *.o

install:
	mv libmgclex.so /usr/local/lib
	ldconfig
	gcc src/main.c -o mgclex -lmgclex
	mv mgclex /usr/local/bin 
	cp src/mgclex.h /usr/include/mgc

clean:
	rm *.o

debug:
	gcc -DDEBUG -g -c src/dfa/re2ast/src/ast.c
	gcc -DDEBUG -g -c src/dfa/re2ast/src/parser.c
	gcc -DDEBUG -g -c src/dfa/re2ast/src/tokens.c 
	gcc -DDEBUG -g -c src/dfa/build_dfa.c
	gcc -DDEBUG -g -c src/dfa/dfa.c
	gcc -DDEBUG -g -c src/dfa/dfastate.c
	gcc -DDEBUG -g -c src/dfa/followpos.c
	gcc -DDEBUG -g -c src/dfa/intset.c
	gcc -DDEBUG -g -c src/dfa/ast_to_dfa.c
	gcc -DDEBUG -g -c src/dfa/statequeue.c
	gcc -DDEBUG -g -c src/dfa/transition.c
	gcc -DDEBUG -g -c src/lexgen.c
	gcc -DDEBUG -g -c src/tokenrules.c
	gcc -DDEBUG -g -c src/util.c
	gcc -DDEBUG -g -c src/readconfig.c
	gcc -DDEBUG -g -c src/mgclex.c
	gcc -DDEBUG -g -c src/main.c
	gcc -DDEBUG *.o -o mgclex