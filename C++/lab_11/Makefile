.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Iinclude

all: bin main

bin:
	mkdir -p bin

main: bin/main.o bin/employees.o include/*.h 
	$(CXX) $(CXXFLAGS) bin/main.o bin/employees.o -o empl_db

bin/main.o: src/main.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/employees.o: src/employees.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/employees.cpp -o bin/employees.o
	
clean:
	rm -rf bin empl_db
