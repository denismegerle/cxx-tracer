#pragma once

#include <assert.h>
#include <omp.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <exception>
#include <initializer_list>

#include "maths/vector.h"

using namespace gem;

/* operator overloads for vectors */
template <typename T, size_t S>
std::ostream &operator<<(std::ostream &strm, const Vector<T, S> &vec) {
  strm << "Vector[" << vec.values.size() << "]"
       << "(|";

  for (auto &elem : vec.values) strm << elem << "|";

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
Vector<T, S> operator-(const Vector<T, S> &a) {
  return a.negate();
};

template <typename T, size_t S>
T operator*(const Vector<T, S> &a, const Vector<T, S> &b) {
  return a.dot(b);
};

template <typename T, size_t S>
Vector<T, S> operator*(const T &scalar, const Vector<T, S> &b) {
  return b.mult(scalar);
};

template <typename T, size_t S>
Vector<T, S> operator*(const Vector<T, S> &a, const T &scalar) {
  return scalar * a;
};

using namespace gem;

template <typename T, size_t S>
Vector<T, S>::Vector(const std::array<T, S> values) : values(values) {
  assert(S == std::size(values));
};

template <typename T, size_t S>
template <typename... Ts>
Vector<T, S>::Vector(const T value, const Ts... vals) : values() {
  std::initializer_list<T> values_list = {vals...};
  auto init_with_one = [](std::array<T, S> *values, T value) {
    values->fill(value);
  };
  auto init_with_s = [](std::array<T, S> *values, T value,
                        std::initializer_list<T> vals) {
    (*values)[0] = value;
    std::copy(std::begin(vals), std::end(vals), std::begin(*values) + 1);
  };

  if (values_list.size() == 0)
    init_with_one(&values, value);
  else if (values_list.size() == S - 1)
    init_with_s(&values, value, values_list);
  else {
    throw;  // for convenience, TODO: proper exceptions
  }
};

/* mathematical functions on vectors */
template <typename T, size_t S>
Vector<T, S> Vector<T, S>::add(const Vector<T, S> other) const {
  std::array<T, S> sum{};

  for (int i = 0; i < this->values.size(); i++) {
    sum[i] = this->values[i] + other.values[i];
  }

  return Vector<T, S>(sum);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::sub(const Vector<T, S> other) const {
  std::array<T, S> diff{};

  for (int i = 0; i < this->values.size(); i++) {
    diff[i] = this->values[i] - other.values[i];
  }

  return Vector<T, S>(diff);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::negate() const {
  std::array<T, S> negation{};

  for (int i = 0; i < this->values.size(); i++) {
    negation[i] = -this->values[i];
  }

  return Vector<T, S>(negation);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::mult(const Vector<T, S> other) const {
  std::array<T, S> prod{};

  for (int i = 0; i < this->values.size(); i++) {
    prod[i] = this->values[i] * other.values[i];
  }

  return Vector<T, S>(prod);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::mult(const T scalar) const {
  std::array<T, S> prod{};

  for (int i = 0; i < this->values.size(); i++) {
    prod[i] = this->values[i] * scalar;
  }

  return Vector<T, S>(prod);
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::div(const Vector<T, S> other) const {
  std::array<T, S> div{};

  for (int i = 0; i < this->values.size(); i++) {
    div[i] = this->values[i] / other.values[i];
  }

  return Vector<T, S>(div);
}

template <typename T, size_t S>
T Vector<T, S>::dot(const Vector<T, S> other) const {
  T prod = 0;

  for (int i = 0; i < this->values.size(); i++) {
    prod += this->values[i] * other.values[i];
  }

  return prod;
}

template <typename T, size_t S>
T Vector<T, S>::norm(const Vector<T, S>::NormType type) const {
  T norm = 0;

  switch (type) {
    case NormType::EUCLIDEAN:
      for (int i = 0; i < this->values.size(); i++) {
        norm += this->values[i] * this->values[i];
      }
      norm = sqrt(norm);
      break;

    case NormType::TAXICAB:
      for (int i = 0; i < this->values.size(); i++) {
        norm += abs(this->values[i]);
      }
      break;

    case NormType::MAX:
      norm = abs(this->values[0]);
      for (int i = 0; i < this->values.size(); i++) {
        if (abs(this->values[i]) > norm) {
          norm = abs(this->values[i]);
        }
      }
      break;
  }

  return norm;
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::cross(const Vector<T, S> other) const {
  if (S != 3) throw;  // we allow crossproducts only for 3d

  Vector<T, S> result(
      this->values[1] * other.values[2] - this->values[2] * other.values[1],
      this->values[2] * other.values[0] - this->values[0] * other.values[2],
      this->values[0] * other.values[1] - this->values[1] * other.values[0]);
  return result;
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::normalize() const {
  if (this->norm() == 0) return Vec3f(0.0f);
  return this->mult(1.0f / this->norm());
}

template <typename T, size_t S>
Vector<T, S> Vector<T, S>::clamp(const Vector<T, S> left,
                                 const Vector<T, S> right) const {
  std::array<T, S> clamped{};

  for (int i = 0; i < this->values.size(); i++) {
    clamped[i] = this->values[i];

    if (this->values[i] < left.values[i]) clamped[i] = left.values[i];
    if (this->values[i] > right.values[i]) clamped[i] = right.values[i];
  }

  return Vector<T, S>(clamped);
}