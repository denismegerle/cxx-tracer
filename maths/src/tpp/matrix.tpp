#pragma once

#include "maths/matrix.h"

#include <assert.h>
#include <array>

using namespace gem;

/* operator overloads for vectors */
template <typename T, size_t S>
std::ostream &operator<<(std::ostream &strm, const gem::Matrix<T, S> &mat) {
  strm << "Matrix[" << mat.length << "]"
       << "(||";

  for (auto &row : mat.values) {
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
Matrix<T, S>::Matrix(std::array<std::array<T, S>, S> values)
    : length(std::size(values)), values(values) {
  assert(S == std::size(values));
}


template <typename T, size_t S>
template <typename... Ts>
Matrix<T, S>::Matrix(const T value, const Ts... vals) : length(S), values() {
  std::initializer_list<T> values_list = {vals...};
  auto init_with_one = [](std::array<std::array<T, S>, S> *values, T value) {
    for (auto &elem : *values)
      elem.fill(value);
  };
  auto init_with_s = [](std::array<std::array<T, S>, S> *values, T value,
                        std::initializer_list<T> vals) {
    (*values)[0][0] = value;

    for (int i = 0; i < S; i++) {
      if (i == 0) {
        std::copy(std::begin(vals), std::begin(vals) + S - 1,
                  std::begin((*values)[i]) + 1);
      } else {
        std::copy(std::begin(vals) + i * S - 1, std::begin(vals) + (i + 1) * S - 1,
                  std::begin((*values)[i]));
      
      }
    }
  };
  auto init_with_d = [](std::array<std::array<T, S>, S> *values, T value,
                        std::initializer_list<T> vals) {
    (*values)[0][0] = value;

    for (int i = 1; i < S; i++) {
      (*values)[i][i] = std::begin(vals)[i - 1];
    }
  };

  if (values_list.size() == 0)
    init_with_one(&values, value);
  else if (values_list.size() == S - 1)
    init_with_d(&values, value, values_list);
  else if (values_list.size() == S * S - 1)
    init_with_s(&values, value, values_list);
  else {
    throw;  // for convenience, TODO: proper exceptions
  }
};

/* mathematical functions on matrices */
template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::add(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> sum{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      sum[i][j] = this->values[i][j] + other.values[i][j];
    }
  }

  return Matrix<T, S>(sum);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::sub(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> diff{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      diff[i][j] = this->values[i][j] - other.values[i][j];
    }
  }

  return Matrix<T, S>(diff);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::mult(const Matrix<T, S> other) const {
  std::array<std::array<T, S>, S> prod{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      prod[i][j] = this->values[i][j] * other.values[i][j];
    }
  }

  return Matrix<T, S>(prod);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::mult(const T scalar) const {
  std::array<std::array<T, S>, S> prod{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      prod[i][j] = scalar * this->values[i][j];
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
        prod[i][j] += this->values[i][k] * other.values[k][j];
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
      prod[i] += this->values[i][k] * other.values[k];
    }
  }

  return Vector<T, S>(prod);
}

template <typename T, size_t S>
Matrix<T, S> Matrix<T, S>::transpose() const {
  std::array<std::array<T, S>, S> trans{};

  for (int i = 0; i < this->length; i++) {
    for (int j = 0; j < this->length; j++) {
      trans[i][j] = this->values[j][i];
    }
  }

  return Matrix<T, S>(trans);
}