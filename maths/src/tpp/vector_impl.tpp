#pragma once

#include <assert.h>
#include <array>
#include <cmath>
#include "maths/vector.h"

/* operator overloads for vectors */
template <typename T, size_t S>
std::ostream &operator<<(std::ostream &strm, const Vector<T, S> &vec) {
  strm << "Vector[" << vec.length << "]"
       << "(|";

  for (auto &elem : vec.val) strm << elem << "|";

  return strm << ")";
};

template <typename T, size_t S>
Vector<T, S> operator+(const Vector<T, S> &a, const Vector<T, S> &b) {
  return a.add(b);
};

template <typename T, size_t S>
Vector<T, S> operator-(const Vector<T, S> &a, const Vector<T, S> &b) {
  return a.sub(b);
};

template <typename T, size_t S>
T operator*(const Vector<T, S> &a, const Vector<T, S> &b) {
  return a.dot(b);
};

template <typename T, size_t S>
Vector<T, S>  operator*(const T &scalar, const Vector<T, S> &b) {
  return b.mult(scalar);
};

template <typename T, size_t S>
Vector<T, S> operator*(const Vector<T, S> &a, const T &scalar) {
  return scalar * a;
};

using namespace gem;

template <typename T, size_t S>
Vector<T, S>::Vector(const std::array<T, S> val)
    : length(std::size(val)), val(val) {
  assert(S == std::size(val));
};

/* mathematical functions on vectors */
template <typename T, size_t S>
Vector<T, S> Vector<T, S>::add(const Vector<T, S> other) const {
  std::array<T, S> sum{};

  for (int i = 0; i < this->length; i++) {
    sum[i] = this->val[i] + other.val[i];
  }

  return Vector<T, S>(sum);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::sub(const Vector<T, S> other) const {
  std::array<T, S> diff{};

  for (int i = 0; i < this->length; i++) {
    diff[i] = this->val[i] - other.val[i];
  }

  return Vector<T, S>(diff);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::mult(const Vector<T, S> other) const {
  std::array<T, S> prod{};

  for (int i = 0; i < this->length; i++) {
    prod[i] = this->val[i] * other.val[i];
  }

  return Vector<T, S>(prod);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::mult(const T scalar) const {
  std::array<T, S> prod{};

  for (int i = 0; i < this->length; i++) {
    prod[i] = this->val[i] * scalar;
  }

  return Vector<T, S>(prod);
}

template <typename T, size_t S>
T Vector<T, S>::dot(const Vector<T, S> other) const {
  T prod = 0;

  for (int i = 0; i < this->length; i++) {
    prod += this->val[i] * other.val[i];
  }

  return prod;
}

template <typename T, size_t S>
T Vector<T, S>::norm(const Vector<T, S>::NormType type) const {
  T norm = 0;

  switch (type) {
    case NormType::EUCLIDEAN:
      for (int i = 0; i < this->length; i++) {
        norm += this->val[i] * this->val[i];
      }
      norm = sqrt(norm);
      break;

    case NormType::TAXICAB:
      for (int i = 0; i < this->length; i++) {
        norm += abs(this->val[i]);
      }
      break;

    case NormType::MAX:
      norm = abs(this->val[0]);
      for (int i = 0; i < this->length; i++) {
        if (abs(this->val[i]) > norm) {
          norm = abs(this->val[i]);
        }
      }
      break;
  }

  return norm;
}
