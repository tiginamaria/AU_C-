#include "employees.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
int main() {
	EmployeesArray db;
	std::string s;
	std::cin >> s;
	while (s != "exit") {
		if (s == "add") {
			int t;
			std::cin >> t;
			Employee *e;
			if (t == 1)
				e = (Employee*) new Developer;
			else 
				e = (Employee*) new SalesManager;
			std::cin >> *e;
			db.add(e);
		} else if (s == "list") {
			std::cout << db;
		} else if (s == "save") {
			std::string f;
			std::cin >> f;		
			std::ofstream fout(f, std::ios::binary | std::ios::out); 
			fout << db;
			fout.close();
		} else if (s == "load") {
			std::string f;
			std::cin >> f;
			std::ifstream fin(f, std::ios::binary | std::ios::in);
			fin >> db;
			fin.close();
		}
		std::cin >> s;
	}
	return 0;
}
