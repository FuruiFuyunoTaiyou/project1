all: shell.o
	gcc shell.o
shell.o: shell.c headers.h
	gcc -c shell.c
run: all
	./a.out
