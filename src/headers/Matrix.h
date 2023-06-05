#ifndef SRC_HEADERS_MATRIX_H_
#define SRC_HEADERS_MATRIX_H_

#define EPS 1e-7

#include <initializer_list>
#include <iostream>

namespace s21 {
template<typename T>
class Matrix {
 private:
  int _rows, _cols;
  T **_matrix;

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);
  explicit Matrix(const std::initializer_list<std::initializer_list<T>> &list);

  ~Matrix();
  int getRows();
  int getCols();
  T **getMatrix();

  void clear();
  void swap(Matrix &other);
  void print() const;
  void operator=(const Matrix &other);
  bool operator==(const Matrix &other);
  bool operator!=(const Matrix &other);
  void operator=(Matrix &&other);
  T &operator()(int i, int j);
  T *operator[](const int i);
};
}  // namespace s21

template<typename T>
s21::Matrix<T>::Matrix() {
    _cols = 0;
    _rows = 0;
    _matrix = nullptr;
}

template<typename T>
s21::Matrix<T>::Matrix(int rows, int cols) {
    _cols = cols;
    _rows = rows;
    _matrix = new T *[_rows];
    for (int i = 0; i < _rows; i++)
        _matrix[i] = new T[_cols]{};
}

template<typename T>
s21::Matrix<T>::Matrix(const Matrix &other) {
    _rows = other._rows;
    _cols = other._cols;
    _matrix = new T *[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new T[_cols];
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

template<typename T>
s21::Matrix<T>::Matrix(Matrix &&other)
    : _cols(other._cols), _rows(other._rows), _matrix(other._matrix) {
    other._cols = other._rows = 0;
    other._matrix = nullptr;
}

template<typename T>
s21::Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &list)
    : Matrix(list.size(), list.begin()->size()) {
    int i = 0, j = 0;
    for (auto item1 : list) {
        for (auto item2 : item1) {
            _matrix[i][j] = item2;
            ++j;
        }
        ++i;
        j = 0;
    }
}

template<typename T>
s21::Matrix<T>::~Matrix() {
    clear();
}

template<typename T>
int s21::Matrix<T>::getRows() { return _rows; }

template<typename T>
int s21::Matrix<T>::getCols() { return _cols; }

template<typename T>
T **s21::Matrix<T>::getMatrix() { return _matrix; }

template<typename T>
void s21::Matrix<T>::clear() {
    if (_matrix != nullptr) {
        for (int i = 0; i < _rows; ++i)
            delete[] _matrix[i];
        delete[] _matrix;
    }
    _matrix = nullptr;
    _rows = 0;
    _cols = 0;
}

template<typename T>
void s21::Matrix<T>::swap(Matrix &other) {
    std::swap(_matrix, other._matrix);
    std::swap(_cols, other._cols);
    std::swap(_rows, other._rows);
}

template<typename T>
void s21::Matrix<T>::operator=(const Matrix &other) {
    clear();
    _cols = other._cols;
    _rows = other._rows;
    _matrix = new T *[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new T[_cols];
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

template<typename T>
void s21::Matrix<T>::operator=(Matrix &&other) {
    clear();
    _cols = other._cols;
    _rows = other._rows;
    _matrix = other._matrix;
    other._matrix = nullptr;
    other._cols = other._rows = 0;
}

template<typename T>
bool s21::Matrix<T>::operator==(const Matrix &other) {
    bool result = true;
    if (other._cols != _cols || other._rows != _rows) {
        result = false;
    } else {
        for (int i = 0; i < _rows && result; ++i) {
            for (int j = 0; j < _cols && result; ++j) {
                if (other._matrix[i][j] != _matrix[i][j]) {
                    result = false;
                }
            }
        }
    }
    return result;
}

template<typename T>
bool s21::Matrix<T>::operator!=(const Matrix &other) {
    return !(*this == other);
}

template<typename T>
T &s21::Matrix<T>::operator()(int i, int j) {
    if (i >= _rows || j >= _cols || i < 0 || j < 0)
        throw std::out_of_range("Index was out of range");
    return _matrix[i][j];
}

template<typename T>
T *s21::Matrix<T>::operator[](const int i) {
    return _matrix[i];
}


#endif  // SRC_HEADERS_MATRIX_H_
