#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <string>
#include <string.h>
#include <cstdio>
#include <cstddef>

class MatrixException {
private:
  std::string message;
public:
  MatrixException(std::string s);
  std::string get();
};

class Matrix {
public:
  Matrix(const std::size_t r = 0, const std::size_t c = 0);
  Matrix(const Matrix& m);
  void load(std::string file);
  ~Matrix();
  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(const std::size_t i, const std::size_t j, const int val);
  int get(const std::size_t i, const std::size_t j) const;
  friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
  void swap(Matrix m);
  Matrix& operator=(Matrix m);
  Matrix operator+(const Matrix& m) const;
  Matrix operator-(const Matrix& m) const;
  Matrix operator*(const Matrix& m) const;

  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  bool operator==(const Matrix& m) const;
  bool operator!=(const Matrix& m) const;
private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

#endif
