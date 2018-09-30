CFLAGS= -Wall -Werror -I include

all: bin main

bin:
	mkdir -p bin

main:  bin/main.o bin/phonebook.o 
	gcc $(CFLAGS)  bin/main.o bin/phonebook.o -o main -lexpat

bin/phonebook.o: src/phonebook.c include/phonebook.h
	gcc $(CFLAGS) -c src/phonebook.c  -o bin/phonebook.o

bin/main.o: src/main.c include/phonebook.h
	gcc $(CFLAGS) -c src/main.c  -o bin/main.o
clean:
	rm -rf main bin

