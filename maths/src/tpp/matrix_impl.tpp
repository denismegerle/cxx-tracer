#pragma once

#include "maths/matrix.h"

#include <assert.h>
#include <array>

/* operator overloads for vectors */
template <typename T, size_t S>
std::ostream &operator<<(std::ostream &strm, const gem::Matrix<T, S> &mat) {
  strm << "Matrix[" << mat.length << "]"
       << "(||";

  for (auto &row : mat.val) {
    for (auto &elem : row) strm << elem << "|";
    strm << "|";
  }

  return strm << ")";
}

template <typename T, size_t S>
Matrix<T, S> operator+(const Matrix<T, S> &a, const Matrix<T, S> &b) {
  return a.add(b);
};

template <typename T, size_t S>
Matrix<T, S> operator-(const Matrix<T, S> &a, const Matrix<T, S> &b) {
  return a.sub(b);
};

template <typename T, size_t S>
Matrix<T, S> operator*(const Matrix<T, S> &a, const Matrix<T, S> &b) {
  return a.dot(b);
};

template <typename T, size_t S>
Matrix<T, S> operator*(const T &scalar, const Matrix<T, S> &b) {
  return b.mult(scalar);
};

template <typename T, size_t S>
Matrix<T, S> operator*(const Matrix<T, S> &a, const T &scalar) {
  return scalar * a;
};

template <typename T, size_t S>
Vector<T, S> operator*(const Vector<T, S> &a, const Matrix<T, S> &b) {
  return b.dot(a);
};

template <typename T, size_t S>
Vector<T, S> operator*(const Matrix<T, S> &a, const Vector<T, S> &b){
  return b * a;
};

using namespace gem;

template <typename T, size_t S>
Matrix<T, S>::Matrix(std::array<std::array<T, S>, S> val)
    : length(std::size(val)), val(val) {
  assert(S == std::size(val));
}

/* mathematical functions on matrices */
template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::add(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> sum{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      sum[i][j] = this->val[i][j] + other.val[i][j];
    }
  }

  return Matrix<T, S>(sum);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::sub(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> diff{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      diff[i][j] = this->val[i][j] - other.val[i][j];
    }
  }

  return Matrix<T, S>(diff);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::mult(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> prod{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      prod[i][j] = this->val[i][j] * other.val[i][j];
    }
  }

  return Matrix<T, S>(prod);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::mult(const T scalar) const {
  std::array<std::array<T, S>, S> prod{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      prod[i][j] = scalar * this->val[i][j];
    }
  }

  return Matrix<T, S>(prod);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::dot(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> prod{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      for (int k = 0; k < this->length; k++) {
        prod[i][j] += this->val[i][k] * other.val[k][j];
      }
    }
  }

  return Matrix<T, S>(prod);
}

template <typename T, size_t S>
Vector<T, S> Matrix<T, S>::dot(const Vector<T, S> other) const {
  std::array<T, S> prod{};

  for (int i = 0; i < this->length; i++) {
    for (int k = 0; k < this->length; k++) {
      prod[i] += this->val[i][k] * other.val[k];
    }
  }

  return Vector<T, S>(prod);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::transpose() const {
  std::array<std::array<T, S>, S> trans{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      trans[i][j] = this->val[j][i];
    }
  }

  return Matrix<T, S>(trans);
}