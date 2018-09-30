CFLAGS= -Wall -Werror -I include

all : bin lab3

bin:
	mkdir -p bin
 
lab3:   bin/main.o bin/clist.o
	gcc $(CFLAGS) -o lab3 -fno-builtin bin/main.o bin/clist.o

bin/main.o: src/main.c include/clist.h 
	gcc $(CFLAGS) -c src/main.c -fno-builtin -o bin/main.o

bin/clist.o: src/clist.c include/clist.h 
	gcc $(CFLAGS) -c src/clist.c -fno-builtin -o bin/clist.o 

clean:
	rm -rf lab3 bin

