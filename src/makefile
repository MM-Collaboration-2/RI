GCC = gcc -Wall -g

test: test.o list.o object.o
	$(GCC) test.o list.o object.o -o test

test.o: test.c
	$(GCC) test.c -c

list.o: list.c
	$(GCC) list.c -c

object.o: object.c
	$(GCC) object.c -c

clear:
	rm *.o test
