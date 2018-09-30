#include <stdint.h>
#include <string.h>
#include <string>
#include <fstream>
#include <algorithm>
#include "employees.h"

Employee::~Employee() {}

Employee::Employee() {}

std::ostream& operator<<(std::ostream& os, Employee& e) {
	(&e)->write(os);
	return os;
}

std::istream& operator>>(std::istream& is, Employee& e) {
	(&e)->read(is);
	return is;
}

std::ofstream& operator<<(std::ofstream& file, Employee& e) {
	(&e)->writef(file);
	return file;
}

std::ifstream& operator>>(std::ifstream& file, Employee& e) {
	(&e)->readf(file);
	return file;
}

//////////////////////////////////////////////////////////////////////

Developer::Developer() {}

Developer::~Developer() {
	delete [] _name;
}

int Developer::salary() const {
	int salary = _base_salary;
	if (_has_bonus) { 
		salary += 1000; 
	}
	return salary;
}

void Developer::read(std::istream& is) {
	std::string s;
	is >> s;
	_name = new char[s.size() + 1];
	for (size_t i = 0; i < s.size(); i++)
		_name[i] = s[i];
	_name[s.size()] = '\0';
	is >> _base_salary >> _has_bonus;
}

void Developer::readf(std::ifstream& file) {
	char ch;
	std::string s;
	file.read(&ch, 1);
	while (ch) {
		s += ch;
		file.read(&ch, 1);
	}
	_name = new char[s.size() + 1];
	for (size_t i = 0; i < s.size(); i++)
		_name[i] = s[i];
	_name[s.size()] = '\0';
	file.read((char*)(&_base_salary), sizeof(_base_salary));
	file.read((char*)(&_has_bonus), sizeof(_has_bonus));
}

void Developer::write(std::ostream& os) const {
	os << "Developer\n";
	os << "Name: " << _name << '\n';
	os << "Base Salary: " << _base_salary << '\n';
	os << "Has bonus: " << (_has_bonus ? '+' : '-') << '\n';
}

void Developer::writef(std::ofstream& file) const {
	int32_t _type = 1;
	file.write((char*)(&_type), sizeof(_type));
	file.write((char*)(_name), strlen(_name) + 1);
	file.write((char*)(&_base_salary), sizeof(_base_salary));
	file.write((char*)(&_has_bonus), sizeof(_has_bonus));
}

//////////////////////////////////////////////////////////////////////

SalesManager::SalesManager() {}

SalesManager::~SalesManager() {
	delete [] _name;
}

int SalesManager::salary() const {
	return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::read(std::istream& is) {
	std::string s;
	is >> s;
	_name = new char[s.size() + 1];
	for (size_t i = 0; i < s.size(); i++)
		_name[i] = s[i];
	_name[s.size()] = '\0';
	is >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::readf(std::ifstream& file) {
	char ch;
	std::string s;
	file.read(&ch, 1);
	while (ch) {
		s += ch;
		file.read(&ch, 1);
	}
	_name = new char[s.size() + 1];
	for (size_t i = 0; i < s.size(); i++)
		_name[i] = s[i];
	_name[s.size()] = '\0';
	file.read((char*)(&_base_salary), sizeof(_base_salary));
	file.read((char*)(&_sold_nm), sizeof(_sold_nm));
	file.read((char*)(&_price), sizeof(_price));
}

void SalesManager::write(std::ostream& os) const {
	os << "Sales Manager\n";
	os << "Name: " << _name << '\n';
	os << "Base Salary: " << _base_salary << '\n';
	os << "Sold items: " << _sold_nm << '\n';
	os << "Item price: " << _price << '\n';
}

void SalesManager::writef(std::ofstream& file) const {
	int32_t _type = 2;
	file.write((char*)(&_type), sizeof(_type));
	file.write((char*)(_name), strlen(_name) + 1);
	file.write((char*)(&_base_salary), sizeof(_base_salary));
	file.write((char*)(&_sold_nm), sizeof(_sold_nm));
	file.write((char*)(&_price), sizeof(_price));
}

//////////////////////////////////////////////////////////////////////

EmployeesArray::EmployeesArray() {
	_size = 0;
	_capasity = 2;
	_employees = new Employee* [_capasity];
}

EmployeesArray::~EmployeesArray() {
	for (int32_t i = 0; i < _size; i++)
		delete _employees[i];
	delete [] _employees;
}

void EmployeesArray::add(Employee *e) {
	_employees[_size++] = e;
	if (_size == _capasity) {
		_capasity *= 2; 
 		Employee ** tmp = new Employee* [_capasity];
 		for (int32_t i = 0; i < _size; i++)
			tmp[i] = _employees[i];
		std::swap(_employees, tmp);
		delete [] tmp;
	}
}

int EmployeesArray::total_salary() const {
	int sum = 0;
	for (int32_t i = 0; i < _size; i++)
		sum += _employees[i]->salary();
	return sum;
}

std::ifstream& operator>>(std::ifstream& file, EmployeesArray& arr) {
	int32_t n;
	file.read((char*)(&n), sizeof(n));
	int32_t type;
	for (int32_t i = 0; i < n; i++) {
		file.read((char*)(&type), sizeof(type));
		Employee *e;
		if (type == 1)
			e = (Employee*) new Developer;
		else 
			e = (Employee*) new SalesManager;
		file >> *e;
		arr.add(e);
	}
	return file;		
}

std::ostream& operator<<(std::ostream& os, const EmployeesArray& arr) {
	for (int32_t i = 0; i < arr._size; i++)
		os << i + 1 << ". " << *(arr._employees[i]);
	os << "== Total salary: " << arr.total_salary() << "\n";
	return os;
}

std::ofstream& operator<<(std::ofstream& file, const EmployeesArray& arr) {
	file.write((char*)(&arr._size), sizeof(arr._size));
	for (int32_t i = 0; i < arr._size; i++)
		file << *(arr._employees[i]);
	return file;
}
