#include <iostream>
#include <string>
#include "huffman.h"

const int symbol_info = 5;
const int size_info = sizeof(int);

void Archiver::Tree::build_codes(Node_ptr node, std::string s) {
	if (!node) return;
	if (node->only)
		s = '1';
	if (node->leaf)
		code[node->c] = s;
	build_codes(node->l, s + '0');
	build_codes(node->r, s + '1');
}

void Archiver::Tree::count_freq(std::ifstream &in) {
	char c;
	while (in >> c)
		freq[c]++, symbols++;
}

bool Archiver::Tree::find_code(bool b, char* c) {
	if(cur_node->only) {
		*c = cur_node->c;
		return 1;
	}
	cur_node = (b ? cur_node->r : cur_node->l);
	if (cur_node->leaf) {
		*c = cur_node->c;
		cur_node = root;
		return 1;
	}
	return 0;
}

std::string Archiver::Tree::get_code(const char c) {
	return code[c];
} 

Archiver::Tree::Node_ptr Archiver::Tree::get_root() const {
	return root;
} 

void Archiver::Tree::set_info(int* codes_cnt, int* symbols_cnt) {
	*codes_cnt = freq.size() * symbol_info;
	*symbols_cnt = symbols;
}

void Archiver::get_info(const int in_sz, const int out_sz, const int extra_sz) {
	std::cout << in_sz << '\n' << out_sz << '\n' << extra_sz << '\n';
}
 

void Archiver::Tree::read_freq(int n, std::ifstream &in) {
	char c;
	for (int i = 0; i < n; i += symbol_info) {
		in.read(&c, sizeof(char));
		in.read(reinterpret_cast<char*>(&freq[c]), sizeof(int));
	}
} 

void Archiver::Tree::write_freq(std::ofstream &out) {
	for (auto x : freq) {
		out.write(&x.first, sizeof(char));
		out.write(reinterpret_cast<char*>(&x.second), sizeof(int));
	}
} 

void Archiver::Tree::build_tree() {
	static const auto comp = [](const Node_ptr n1, const Node_ptr n2) {
		return n1->count < n2->count;
	};
	std::multiset<Node_ptr, decltype(comp)> st(comp);
	for (auto x : freq) {
		auto node = std::make_shared<Node>(x.first, x.second, 1, NULL, NULL);
		st.insert(node);
	}
	
	if(st.size() == 0) {
		root = NULL;
		return;
	}
	
	if(st.size() == 1) {
		root = *st.begin();
		root->only = 1;
		cur_node = root;
		st.erase(st.begin());
		return;
	}
	
	while(st.size() != 2) {
		Node_ptr n1 = *st.begin();
		st.erase(st.begin());
		Node_ptr n2 = *st.begin();
		st.erase(st.begin());
		Node_ptr node = std::make_shared<Node>(n1->count + n2->count, 0, n1, n2);
		st.insert(node);
	}
	
	Node_ptr n1 = *st.begin();
	st.erase(st.begin());
	Node_ptr n2 = *st.begin();
	st.erase(st.begin());
	Node_ptr node = std::make_shared<Node>(n1->count + n2->count, 0, n1, n2);
	root = node;
	cur_node = root;
	st.insert(node);
}


void Archiver::Binary_IO::buf_accum(std::ifstream &in) {
	binary_sz++;
	in.read(&buf, 1);
	pos = 0;
}	
		
void Archiver::Binary_IO::buf_flash(std::ofstream &out) {
	binary_sz++;
	out.write(&buf, 1);
	buf = 0, pos = 0;
}
	
void Archiver::Binary_IO::write_bit(std::ofstream &out, bool b) {
	buf |= (b << pos);
	pos++;
	if (pos == buf_end)
		buf_flash(out);
}

bool Archiver::Binary_IO::read_bit(std::ifstream &in) {
	if (pos == buf_end)
		buf_accum(in);
	pos++;
	return (1 & (buf >> (pos - 1)));
}

void Archiver::Binary_IO::buf_code(std::string code, std::ofstream &out) {
	for (size_t i = 0; i < code.size(); i++)
		write_bit(out, code[i] == '1' ? 1 : 0);
}

void Archiver::Binary_IO::start(std::ifstream &in) {
	buf_accum(in);
}

void Archiver::Binary_IO::end(std::ofstream &out) {
	buf_flash(out);
}

void Archiver::write_header(std::ofstream &out) {
	printer.header_sz += 2 * size_info;
	out.write(reinterpret_cast<char*>(&printer.header_sz), sizeof(int));
	out.write(reinterpret_cast<char*>(&printer.file_sz), sizeof(int));
	tree.write_freq(out);
}
	
void Archiver::coder(std::ifstream &in, std::ofstream &out) {
	tree.count_freq(in);
	tree.build_tree();
	tree.build_codes(tree.get_root(), "");
	tree.set_info(&printer.header_sz, &printer.file_sz);
	
	write_header(out);
	
	in.clear(), in.seekg(0);
	char c;
	while (in >> c)
		printer.buf_code(tree.get_code(c), out);
	printer.end(out);
	get_info(printer.file_sz, printer.binary_sz, printer.header_sz);
}

void Archiver::read_header(std::ifstream &in) {
	in.read(reinterpret_cast<char*>(&reader.header_sz), sizeof(int));
	in.read(reinterpret_cast<char*>(&reader.file_sz), sizeof(int));
	tree.read_freq(reader.header_sz - 2 * size_info, in);
}

void Archiver::decoder(std::ifstream &in, std::ofstream &out) {
	read_header(in);
	tree.build_tree();
	reader.start(in);
	
	bool found;
	char c;
	for (int i = 0; i < reader.file_sz; i++) {
		found = 0;
		while (!found)
			found = tree.find_code(reader.read_bit(in), &c);
		out << c;
	}
	get_info(reader.binary_sz, reader.file_sz, reader.header_sz);
}
