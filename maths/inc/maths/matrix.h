#pragma once

#include <array>

namespace gem {

template <typename T,
          size_t S>  // forward declaration of Vector since including
class Vector;        // header would be circular dependency

/// <summary>
/// We use size_t to provide special implementations for operations.
/// </summary>
template <typename T, size_t S>
class Matrix {
 private:
  size_t length;
  std::array<std::array<T, S>, S> val;

  /* operator overloads for vectors */
  template <typename T, size_t S>
  friend std::ostream &operator<<(std::ostream &strm, const Matrix<T, S> &mat);

  template <typename T, size_t S>
  friend Matrix<T, S> operator+(const Matrix<T, S> &a, const Matrix<T, S> &b);

  template <typename T, size_t S>
  friend Matrix<T, S> operator-(const Matrix<T, S> &a, const Matrix<T, S> &b);

  template <typename T, size_t S>
  friend Matrix<T, S> operator*(const Matrix<T, S> &a, const Matrix<T, S> &b);

  template <typename T, size_t S>
  friend Matrix<T, S> operator*(const T &scalar, const Matrix<T, S> &b);

  template <typename T, size_t S>
  friend Matrix<T, S> operator*(const Matrix<T, S> &a, const T &scalar);

  template <typename T, size_t S>
  friend Vector<T, S> operator*(const Vector<T, S> &a, const Matrix<T, S> &b);

  template <typename T, size_t S>
  friend Vector<T, S> operator*(const Matrix<T, S> &a, const Vector<T, S> &b);

  // TODO / (inverse mult) implementieren

 public:
  enum class NormType {
    EUCLIDEAN,
    TAXICAB,
    MAX,
  };

  Matrix(std::array<std::array<T, S>, S> val);
  // TODO: implement diag, I, ... initialization

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

#include "matrix_impl.tpp"

}  // namespace gem