.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Iinclude

all: bin main

bin:
	mkdir -p bin

main: bin/main.o include/*.h 
	$(CXX) $(CXXFLAGS) bin/main.o -o lab_12

bin/main.o: src/main.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

clean:
	rm -rf bin lab_12
