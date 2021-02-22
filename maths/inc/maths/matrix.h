#pragma once

#include <array>
#include <iostream>

namespace gem {

template <typename T,
          size_t S>  // forward declaration of Vector since including
class Vector;        // header would be circular dependency

/// <summary>
/// We use size_t to provide special implementations for operations.
/// </summary>
template <typename T, size_t S>
class Matrix {
 public:
  enum class NormType {
    EUCLIDEAN,
    TAXICAB,
    MAX,
  };

  size_t length;
  std::array<std::array<T, S>, S> values;

  Matrix(std::array<std::array<T, S>, S> values);
  template <typename... Ts>
  Matrix(const T value, const Ts... values);
  // TODO: implement diag, I, ... initialization, inverse of matrix

  /* mathematical functions on matrices */
  Matrix<T, S> add(const Matrix<T, S> other) const;
  Matrix<T, S> sub(const Matrix<T, S> other) const;
  Matrix<T, S> mult(const Matrix<T, S> other) const;  // elementwise mult!
  Matrix<T, S> mult(const T scalar) const;
  Matrix<T, S> dot(const Matrix<T, S> other) const;
  Vector<T, S> dot(const Vector<T, S> other) const;

  Matrix<T, S> transpose() const;
  T norm(const NormType type = NormType::EUCLIDEAN) const;
  T det() const;
  T trace() const;

  // Vec<T, S> cross(const Vec<T, S> other);
  // Vec<T, S> normal();
  // Vec<T, S> normalize();
};

typedef Matrix<float, 2> Mat2f;
typedef Matrix<float, 3> Mat3f;
typedef Matrix<float, 4> Mat4f;
typedef Matrix<int, 3> Mat3i;
typedef Matrix<int, 3> Mat3i;

}  // namespace gem

#include "matrix.tpp"