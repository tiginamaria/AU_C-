.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Iinclude -g

all: bin main

bin:
	mkdir -p bin

main: bin/main.o bin/matrix.o include/*.h 
	$(CXX) $(CXXFLAGS) bin/main.o bin/matrix.o -o lab_14

bin/main.o: src/main.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/matrix.o: src/matrix.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/matrix.cpp -o bin/matrix.o

clean:
	rm -rf bin lab_14
