all: program6
run: program6
	./program6
memcheck:program6
	valgrind ./program6
program6: program6.o bst.o bst.h
	gcc -g program6.o bst.o -o program6
program6.o: program6.c bst.h
	gcc -g -c program6.c -o program6.o
bst.o: bst.c bst.h
	gcc -g -c bst.c -o bst.o
clean:
	rm *.o program6