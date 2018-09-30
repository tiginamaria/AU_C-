#include "matrix.h"
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

MatrixException::MatrixException(std::string s) : message(s) {}

std::string MatrixException::get() {
	return message;
}

Matrix::Matrix(const size_t r, const size_t c) {
	_rows = r;
	_cols = c;
	if (r > 0 && c > 0) {
		_data = new int*[_rows];
		for (size_t i = 0; i < _rows; i++) {
			_data[i] = new int [_cols];
			for (size_t j = 0; j < _cols; j++)
				_data[i][j] = 0;
		}
	} else
		_data = NULL;
}

Matrix::Matrix(const Matrix& m) {
	_rows = m._rows;
	_cols = m._cols;
	if (_rows > 0 && _cols > 0) {
		_data = new int*[_rows];
		for (size_t i = 0; i < _rows; i++) {
			_data[i] = new int [_cols];
			for (size_t j = 0; j < _cols; j++) 
				_data[i][j] = m._data[i][j];
		}	
	} else 
		_data = NULL;
}

void Matrix::load(std::string file) {
	std::ifstream in(file);
	size_t r, c;
	in >> r >> c;
	Matrix tmp(r, c);
	swap(tmp);
	for (size_t i = 0; i < tmp._rows; i++)
		for (size_t j = 0; j < tmp._cols; j++) 
			in >> _data[i][j];
}

Matrix::~Matrix() {
	for (size_t i = 0; i < _rows; i++)
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
	if (i >= _rows || j >= _cols)
		throw(MatrixException("ACCESS: bad index."));
	_data[i][j] = val;
}

int Matrix::get(const std::size_t i, const std::size_t j) const {
	if (i >= _rows || j >= _cols)
		throw(MatrixException("ACCESS: bad index."));
	return _data[i][j];
}

void Matrix::swap(Matrix m) {
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	std::swap(_data, m._data);
}

Matrix& Matrix::operator=(Matrix m) {
	swap(m);
	return *this;
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
	if (m._rows != _rows || m._cols != _cols)
		throw(MatrixException("ADD: dimensions do not match."));
	for (std::size_t i = 0; i < _rows; i++) 
		for (std::size_t j = 0; j < _cols; j++) 
			_data[i][j] += m._data[i][j];
  	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	if (m._rows != _rows || m._cols != _cols)
		throw(MatrixException("ADD: dimensions do not match."));
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
	if (m._rows != _cols)
		throw(MatrixException("MUL: #arg1.columns != #arg2.rows."));
	Matrix tmp(_rows, m._cols);
	for (std::size_t i = 0; i < _rows; i++) 
		for (size_t j = 0; j < m._cols; j++) 
			for (size_t u = 0; u < _cols; u++) 
				tmp._data[i][j] += _data[i][u] * m._data[u][j];
  	return tmp;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	for (size_t i = 0; i < m._rows; i++) {
		for (size_t j = 0; j < m._cols; j++)
			os << m._data[i][j] << ' ';
		os << '\n';
	}
	return os;
} 
