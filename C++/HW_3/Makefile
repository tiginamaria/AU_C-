.PHONY: all clean test

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Iinclude -g

all: bin huffman

test: bin test_huffman

bin:
	mkdir -p bin

huffman: bin/main.o bin/huffman.o include/*.h 
	$(CXX) $(CXXFLAGS) bin/main.o bin/huffman.o -o huffman

bin/main.o: src/main.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/huffman.o: src/huffman.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c src/huffman.cpp -o bin/huffman.o
	
test_huffman: bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o include/*.h 
	$(CXX) $(CXXFLAGS) bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o -o test_huffman
	
bin/test.o: test/test.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c test/test.cpp -o bin/test.o
	
bin/autotest.o: test/autotest.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c test/autotest.cpp -o bin/autotest.o

bin/huffman_test.o: include/*.h test/huffman_test.cpp
	$(CXX) $(CXXFLAGS) -c test/huffman_test.cpp -o bin/huffman_test.o
		
clean:
	rm -rf bin huffman test_huffman
