mgclex:
	gcc -c -fPIC src/dfa/re2ast/src/ast.c
	gcc -c -fPIC src/dfa/re2ast/src/parser.c
	gcc -c -fPIC src/dfa/re2ast/src/tokens.c 
	gcc -c -fPIC src/dfa/build_dfa.c
	gcc -c -fPIC src/dfa/dfa.c
	gcc -c -fPIC src/dfa/dfastate.c
	gcc -c -fPIC src/dfa/followpos.c
	gcc -c -fPIC src/dfa/intset.c
	gcc -c -fPIC src/vector.c
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
	cp mgclex /usr/local/bin 
	cp src/mgclex.h /usr/include/mgc

clean:
	rm *.o

debug:
	gcc -c -DDEBUG -fPIC src/dfa/re2ast/src/ast.c
	gcc -c -DDEBUG  -fPIC src/dfa/re2ast/src/parser.c
	gcc -c -DDEBUG  -fPIC src/dfa/re2ast/src/tokens.c 
	gcc -c  -DDEBUG -fPIC src/dfa/build_dfa.c
	gcc -c  -DDEBUG -fPIC src/dfa/dfa.c
	gcc -c  -DDEBUG -fPIC src/dfa/dfastate.c
	gcc -c  -DDEBUG -fPIC src/dfa/followpos.c
	gcc -c  -DDEBUG -fPIC src/dfa/intset.c
	gcc -c  -DDEBUG -fPIC src/vector.c
	gcc -c  -DDEBUG -fPIC src/dfa/ast_to_dfa.c
	gcc -c  -DDEBUG -fPIC src/dfa/statequeue.c
	gcc -c  -DDEBUG -fPIC src/dfa/transition.c
	gcc -c  -DDEBUG -fPIC src/lexgen.c
	gcc -c  -DDEBUG -fPIC src/tokenrules.c
	gcc -c  -DDEBUG -fPIC src/util.c
	gcc -c  -DDEBUG -fPIC src/readconfig.c
	gcc -c  -DDEBUG -fPIC src/mgclex.c
	gcc  -DDEBUG  -shared -o libmgclex.so *.o