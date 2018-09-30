CFLAGS = -Werror -Wall -I include
all : bin main 

bin:
	mkdir -p bin

main: bin/mergesort.o bin/main.o
	gcc $(CFLAGS) -o ms_cli -fno-builtin bin/mergesort.o bin/main.o 

bin/mergesort.o: src/mergesort.c include/mergesort.h
	gcc $(CFLAGS) -c src/mergesort.c -fno-builtin -o bin/mergesort.o

bin/main.o: src/main.c include/mergesort.h
	gcc $(CFLAGS) -c src/main.c -fno-builtin -o bin/main.o

clean:
	rm -rf ms_cli bin 

