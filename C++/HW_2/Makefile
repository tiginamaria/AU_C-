.PHONY: all board_test clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic

all: main

bin:
	mkdir -p bin

main: src/main.cpp bin/Board.o bin/BoardView.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<
	
board_test: Test/test.cpp bin/Board.o bin/t_Test.o bin/t_BoardTest.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/t_%.o: Test/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin main board_test

