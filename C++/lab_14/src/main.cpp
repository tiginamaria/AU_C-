#include "matrix.h"
#include <iostream>
#include <string>

int main() {
	std::string s, f;
	char ch;
	int id, id1, id2;
	size_t i, j;
	Matrix mtx[10];
	std::cin >> s;
	while(s != "exit") {
		try {
			if (s == "load") {
				std::cin >> ch >> id >> f;
				mtx[id].load(f);
			}
			if (s == "mul") {
				std::cin >> ch >> id1 >> ch >> id2;
				mtx[id1] *= mtx[id2];
			}
			if (s == "add") {
				std::cin >> ch >> id1 >> ch >> id2;
				mtx[id1] += mtx[id2];
			}
			if (s == "print") {
				std::cin >> ch >> id;
				std::cout << mtx[id];
			}
			if (s == "elem") {
				std::cin >> ch >> id >> i >> j;
				std::cout << mtx[id].get(i, j) << '\n';
			}
		}
		catch (MatrixException& e) {
			std::cout << e.get() << '\n';
		}
		std::cin >> s;	
	}
	return 0;
}
