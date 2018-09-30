CFLAGS= -Wall -Werror -I include

all: main

main:   bin/main.o bin/clist.o bin/position.o
	gcc $(CFLAGS) -o main bin/main.o bin/clist.o bin/position.o

bin/main.o: src/main.c include/clist.h include/position.h
	gcc $(CFLAGS) -c src/main.c -o bin/main.o

bin/clist.o: src/clist.c include/clist.h 
	gcc $(CFLAGS) -c src/clist.c -o bin/clist.o 

bin/position.o: src/clist.c include/position.h include/clist.h 
	gcc $(CFLAGS) -c src/position.c -o bin/position.o 

clean:
	rm -r main bin/*

