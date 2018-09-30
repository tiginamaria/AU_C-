#include "my_vector.h"
#include <stdio.h>
#include <assert.h>
#include <algorithm>

MyVector::MyVector(): _sz(0), _cp(2), _data(new int [_cp]){}
MyVector::MyVector(std::size_t init_capacity): _sz(0), _cp(init_capacity), _data(new int [_cp]){}

void MyVector::set(std::size_t index, int value) {
	assert(index >= 0 && index < _sz);
	_data[index] = value;
}
int MyVector::get(std::size_t index) {
	assert(index >= 0 && index < _sz);
	return _data[index];
}

std::size_t MyVector::size() {
	return _sz;
}

std::size_t MyVector::capacity() {
	return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
	if (new_capacity > _cp) {
		int *new_data = new int [new_capacity];

		for (std::size_t i = 0; i < _sz; i++)
			new_data[i] = _data[i];

		delete[] _data;
		_data = new_data;	
		_cp = new_capacity;
	} 
		
}
void MyVector::resize(std::size_t new_size) {
	if (new_size > _cp) 
		reserve(std::max(new_size, 2 * _cp));

	for (std::size_t i = _sz; i < new_size; i++)
		_data[i] = 0;

	_sz = new_size;
}
  
void MyVector::push_back(int value) {
	if (_sz >= _cp) 
		reserve(2 * _cp);

	_data[_sz] = value;
	_sz++;		
}

void MyVector::insert(std::size_t index, int value) {
	assert(index >= 0 && index < _sz);
	if (_sz >= _cp) 
		reserve(2 * _cp);

	for (std::size_t i = _sz; i > index; i--) 
		_data[i] = _data[i - 1];

	_data[index] = value;
	_sz++;
}

void MyVector::erase(std::size_t index) {
	assert(index >= 0 && index < _sz);
	for (std::size_t i = index + 1; i < _sz; i++)
		_data[i - 1] = _data[i];
	_sz--;	
}

MyVector::~MyVector() {
	delete[] _data;
	_sz = 0;
	_cp = 0;
}

