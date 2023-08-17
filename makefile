lt = ../littletest/littletest.c
c = gcc -Wall -g
os = test.o chars.o nodes.o littletest.o associations.o lexer.o

test: $(os)
	$(c) $(os) -o test

test.o: test.c
	$(c) test.c -c

chars.o: chars.c
	$(c) chars.c -c

nodes.o: nodes.c
	$(c) nodes.c -c

associations.o: associations.c
	$(c) associations.c -c

lexer.o: lexer.c
	$(c) lexer.c -c

littletest.o: $(lt)
	$(c) $(lt) -c
clear:
	rm *.o test
