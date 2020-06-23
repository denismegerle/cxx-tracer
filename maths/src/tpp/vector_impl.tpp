#pragma once

#include <assert.h>
#include <array>
#include <cmath>
#include <initializer_list>
#include <exception>
#include <algorithm>

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
Vector<T, S>::Vector(const std::array<T, S> value)
    : length(std::size(value)), val(value) {
  assert(S == std::size(value));
};

template <typename T, size_t S>
template<typename... Ts>
Vector<T, S>::Vector(const T value, const Ts... values)
    : length(S) {
  std::initializer_list<T> values_list = {values...};
  auto init_with_one = [](std::array<T, S> *val, T value) {
    *val = std::array<T, S>();
    val->fill(value);
  };
  auto init_with_s = [](std::array<T, S> *val, T value, std::initializer_list<T> values) {
    *val = std::array<T, S>();
    (*val)[0] = value;
    std::copy(std::begin(values), std::end(values), std::begin(*val) + 1);
  };

  if (values_list.size() == 0)
    init_with_one(&val, value);
  else if (values_list.size() == S - 1)
    init_with_s(&val, value, values_list);
  else {
    throw;  // for convenience, TODO: proper exceptions
  }
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

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::cross(const Vector<T, S> other) const {
  if (S != 3) throw; // we allow crossproducts only for 3d

  Vector<T, S> result(
    this->val[1] * other.val[2] - this->val[2] * other.val[1],
    this->val[2] * other.val[0] - this->val[0] * other.val[2],
    this->val[0] * other.val[1] - this->val[1] * other.val[0]
  );
  return result;
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::normalize() const {
  // ignoring the cast 0/0/0, TODO: throw exception or return 000?
  return this->mult(1.0f / this->norm());
}