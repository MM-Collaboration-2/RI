lt = ../littletest/littletest.c
c = gcc -Wall -g

test: test.o chars.o nodes.o littletest.o associations.o
	$(c) test.o chars.o nodes.o littletest.o associations.o -o test

test.o: test.c
	$(c) test.c -c

chars.o: chars.c
	$(c) chars.c -c

nodes.o: nodes.c
	$(c) nodes.c -c

associations.o: associations.c
	$(c) associations.c -c

littletest.o: $(lt)
	$(c) $(lt) -c
clear:
	rm *.o test
