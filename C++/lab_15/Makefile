.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++14 -Wall -pedantic -Iinclude

all: bin main

bin:
	mkdir -p bin

main: bin/smoke_test.o include/*.h 
	$(CXX) $(CXXFLAGS) bin/smoke_test.o -o smoke_test

bin/smoke_test.o: src/smoke_test.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/smoke_test.cpp -o bin/smoke_test.o

clean:
	rm -rf bin smoke_test
