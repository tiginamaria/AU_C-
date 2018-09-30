#pragma once
#include <cstddef>
#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <set>

class Node {
	typedef std::shared_ptr<Node> Node_ptr;
	
public:
	char c;
	int count;
	bool leaf = 0;
	Node_ptr l, r;
	bool only = 0;
	
	Node(int cnt, bool isleaf, Node_ptr l, Node_ptr r) : count(cnt), leaf(isleaf), l(l), r(r) { }
	Node(char c, int cnt, bool isleaf, Node_ptr l, Node_ptr r) : c(c), count(cnt), leaf(isleaf), l(l), r(r) { }
	
	bool operator<(Node& n) {
		return count < n.count;
	}
};

class Archiver {
	typedef std::shared_ptr<Node> Node_ptr;
	friend class HuffmanTest;
	
private:
	class Tree {
		typedef std::shared_ptr<Node> Node_ptr;
		friend class HuffmanTest;
		friend class Node;
		
	private:
		std::map<char, int> freq;
		std::unordered_map<char, std::string> code;
		int symbols = 0;
		
	public:
		Tree(){ }
		void build_tree();
		void build_codes(Node_ptr node, std::string s);
		void count_freq(std::ifstream &in);
		bool find_code(bool b, char* c);
		std::string get_code(const char c);
		Node_ptr get_root() const;
		void set_info(int* codes_cnt, int* symbols_cnt);
		void read_freq(int n, std::ifstream &in);
		void write_freq(std::ofstream &out);
		
	private:	
		Node_ptr root;
		Node_ptr cur_node;
	};
	
	class Binary_IO {
	private:
		char buf = 0;
		const int buf_end = 8;
		int pos = 0;
		
	public:	
		int header_sz = 0, file_sz = 0, binary_sz = 0;
		
		void start(std::ifstream &in);
		void end(std::ofstream &out);
		void buf_code(std::string code, std::ofstream &out);
		bool read_bit(std::ifstream &in);
		void write_bit(std::ofstream &out, bool b);
		void buf_flash(std::ofstream &out);	
		void buf_accum(std::ifstream &in);	
	};
	
private:
	Tree tree;
	Binary_IO printer;
	Binary_IO reader;
	
	void read_header(std::ifstream &in);	
	void write_header(std::ofstream &out);
	
public:
	~Archiver() { };
	void get_info(const int in_sz, const int out_sz, const int extra_sz);
	void coder(std::ifstream &in, std::ofstream &out);
	void decoder(std::ifstream &in, std::ofstream &out);
};


