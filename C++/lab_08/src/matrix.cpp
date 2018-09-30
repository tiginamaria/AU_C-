#include "matrix.h"
#include <assert.h>
#include <algorithm>

Matrix::Matrix(const std::size_t r, const std::size_t c) {
	_rows = r;
	_cols = c;
	_data = new int* [_rows];
	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = new int [_cols];
		for (std::size_t j = 0; j < _cols; j++) 
			_data[i][j] = 0;
	}	
}

Matrix::Matrix(const Matrix& m) {
	_rows = m._rows;
	_cols = m._cols;
	_data = new int*[_rows];
	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = new int [_cols];
		for (std::size_t j = 0; j < _cols; j++) 
			_data[i][j] = m._data[i][j];
	}	
}

Matrix::~Matrix() {
	for (std::size_t i = 0; i < _rows; i++)
		delete [] _data[i];
	delete [] _data;
	_rows = 0;
	_cols = 0;
}

	
std::size_t Matrix::get_rows() const { 
	return _rows; 
}

std::size_t Matrix::get_cols() const { 
	return _cols; 
}

void Matrix::set(const std::size_t i, const std::size_t j, const int val) {
	assert(i < _rows && j < _cols);
	_data[i][j] = val;
}

int Matrix::get(const std::size_t i, const std::size_t j) const {
	assert(i < _rows && j < _cols);
	return _data[i][j];
}

void Matrix::print(FILE* f) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) 
			fprintf(f, "%d ", _data[i][j]);
		fprintf(f, "\n");
	}
}

Matrix& Matrix::swap(Matrix& m) {
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	std::swap(_data, m._data);
	return *this;
}

Matrix& Matrix::operator=(Matrix m) {
	return swap(m);
} 

bool Matrix::operator==(const Matrix& m) const {
	if (m._rows != _rows || m._cols != _cols)
		return false;
	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++) 
			if (_data[i][j] != m._data[i][j]) 
				return false;		
  	return true;
}

bool Matrix::operator!=(const Matrix& m) const {
	return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
	assert(m._rows == _rows && m._cols == _cols);
	for (std::size_t i = 0; i < _rows; i++) 
		for (std::size_t j = 0; j < _cols; j++) 
			_data[i][j] += m._data[i][j];
  	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	assert(m._rows == _rows && m._cols == _cols);
	for (std::size_t i = 0; i < _rows; i++) 
		for (std::size_t j = 0; j < _cols; j++) 
			_data[i][j] -= m._data[i][j];
  	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  	return *this = *this * m;
}

Matrix Matrix::operator+(const Matrix& m) const {
  	return Matrix(*this) += m;
}

Matrix Matrix::operator-(const Matrix& m) const {
  	return Matrix(*this) -= m;
}

Matrix Matrix::operator*(const Matrix& m) const {
	assert(m._rows == _cols);
	Matrix tmp(_rows, m._cols);
	for (std::size_t i = 0; i < _rows; i++) 
		for (std::size_t j = 0; j < m._cols; j++) 
			for (std::size_t u = 0; u < _cols; u++) 
				tmp._data[i][j] += _data[i][u] * m._data[u][j];
  	return tmp;
}
