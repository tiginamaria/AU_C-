#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <assert.h>
#include "huffman.h"
#include "huffman_test.h"

void HuffmanTest::runAllTests() {
    test_count_freq();
    test_build_tree();
    test_build_codes();
    test_coder_decoder();
}
	
void HuffmanTest::test_count_freq() {
    Archiver a;
	std::ofstream out("in");
	out << "?aaa?BBaa1B?Bcc1.";
	out.close();
	
	std::ifstream in("in");
	in >> std::noskipws;
	a.tree.count_freq(in);
	in.close();
    DO_CHECK((*a.tree.freq.find('a')).second == 5);
    DO_CHECK((*a.tree.freq.find('B')).second == 4);
    DO_CHECK((*a.tree.freq.find('c')).second == 2);
    DO_CHECK((*a.tree.freq.find('?')).second == 3);
    DO_CHECK((*a.tree.freq.find('.')).second == 1);
    DO_CHECK((*a.tree.freq.find('1')).second == 2);
    DO_CHECK(a.tree.freq.size() == 6);
}

void HuffmanTest::test_build_tree() {
    Archiver a;
	a.tree.freq.insert({'?', 2});
	a.tree.freq.insert({'a', 5});
	a.tree.freq.insert({'B', 4});
	a.tree.freq.insert({'1', 2});
	a.tree.freq.insert({'c', 3});
	a.tree.freq.insert({'.', 1});
	a.tree.build_tree();
	DO_CHECK(a.tree.root != NULL);
	DO_CHECK((a.tree.root->l->r)->c == 'B');
	DO_CHECK((a.tree.root->l->l->r)->c == '1');
	DO_CHECK((a.tree.root->l->l->l)->c == '.');
	DO_CHECK((a.tree.root->r->l)->c == 'a');
	DO_CHECK((a.tree.root->r->r->l)->c == '?');
	DO_CHECK((a.tree.root->r->r->r)->c == 'c');
}

void HuffmanTest::test_build_codes() {
    Archiver a;
	a.tree.freq.insert({'?', 2});
	a.tree.freq.insert({'a', 5});
	a.tree.freq.insert({'B', 4});
	a.tree.freq.insert({'1', 2});
	a.tree.freq.insert({'c', 3});
	a.tree.freq.insert({'.', 1});
	a.tree.build_tree();
	a.tree.build_codes(a.tree.root, "");
	DO_CHECK(a.tree.code['B'] == "01");
	DO_CHECK(a.tree.code['1'] == "001");
	DO_CHECK(a.tree.code['.'] == "000");
	DO_CHECK(a.tree.code['a'] == "10");
	DO_CHECK(a.tree.code['?'] == "110");
	DO_CHECK(a.tree.code['c'] == "111");
}

void HuffmanTest::test_coder_decoder() {
	std::ifstream in_1("tester_in");
	in_1 >> std::noskipws;
	std::ofstream out_1("tester_binary", std::ofstream::binary);
	Archiver a_1;
	a_1.coder(in_1, out_1);
	in_1.close();
	out_1.close();
	std::ifstream in_2("tester_binary", std::ifstream::binary);
	std::ofstream out_2("tester_out");
	Archiver a_2;
	a_2.decoder(in_2, out_2);
	in_2.close();
	out_2.close();
	std::ifstream file_in("tester_in");
	std::ifstream file_out("tester_out");
	std::string line1, line2;
	bool equal = 1;
	while (std::getline(file_in, line1)) {
		if(!in_2.eof())
        	std::getline(file_out, line2);
        else 
        	equal = 0;
        if(strcmp(line1.c_str(), line2.c_str()))
        	equal = 0;
    }
    file_in.close();
	file_out.close();
    DO_CHECK(equal);
}















