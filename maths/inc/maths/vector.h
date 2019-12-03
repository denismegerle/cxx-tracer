#pragma once

#include <array>
#include <iostream>

namespace gem {

template <typename T,
          size_t S>  // forward declaration of Vector since including
class Matrix;        // header would be circular dependency

/// <summary>
/// We use size_t to provide special implementations for operations.
/// </summary>
template <typename T, size_t S>
class Vector {
 private:
  size_t length;
  std::array<T, S> val;

  /* operator overloads for vectors */
  template <typename T, size_t S>
  friend std::ostream &operator<<(std::ostream &strm, const Vector<T, S> &vec);

  template <typename T, size_t S>
  friend Vector<T, S> operator+(const Vector<T, S> &a, const Vector<T, S> &b);

  template <typename T, size_t S>
  friend Vector<T, S> operator-(const Vector<T, S> &a, const Vector<T, S> &b);

  template <typename T, size_t S>
  friend T operator*(const Vector<T, S> &a, const Vector<T, S> &b);

  template <typename T, size_t S>
  friend Vector<T, S> operator*(const T &scalar, const Vector<T, S> &b);

  template <typename T, size_t S>
  friend Vector<T, S> operator*(const Vector<T, S> &a, const T &scalar);

 public:
  enum class NormType {  // TODO throw this into another file, make it
                         // standalone
    EUCLIDEAN,
    TAXICAB,
    MAX,
  };

  Vector(){};
  Vector(const std::array<T, S> val);

  /* mathematical functions on vectors */
  Vector<T, S> add(const Vector<T, S> other) const;
  Vector<T, S> sub(const Vector<T, S> other) const;
  Vector<T, S> mult(const Vector<T, S> other) const;
  Vector<T, S> mult(const T scalar) const;
  T dot(const Vector<T, S> other) const;
  T norm(const NormType type = NormType::EUCLIDEAN) const;

  // Vec<T, S> cross(const Vec<T, S> other);
  // Vec<T, S> normal();
  // Vec<T, S> normalize();

  // TODO: <outer product>, <reflect>, <refract>
  // TODO: implement cross, normal, normalize

  /* friend functions that need privates from this class */
  friend Vector<T, S> Matrix<T, S>::dot(const Vector<T, S> other) const;
};

/* static vec class function definitions */	// TODO implement static stuff
template <typename T, size_t S>
Vector<T, S> add(const Vector<T, S> &a, const Vector<T, S> &b);

template <typename T, size_t S>
Vector<T, S> sub(const Vector<T, S> &a, const Vector<T, S> &b);

template <typename T, size_t S>
Vector<T, S> mult(const Vector<T, S> &a, const Vector<T, S> &b);

template <typename T, size_t S>
T dot(const Vector<T, S> &a, const Vector<T, S> &b);

template <typename T, size_t S>
T norm(const Vector<T, S> &a);

/*
template <typename T, size_t S>
Vec<T, S> cross(const Vec<T, S> &a, const Vec<T, S> &b);

template <typename T, size_t S>
Vec<T, S> normal(const Vec<T, S> &a);

template <typename T, size_t S>
Vec<T, S> normalize(const Vec<T, S> &a);
*/

/* typedefs for commonly used vectors */
typedef Vector<float, 3> Vec3f;
typedef Vector<float, 4> Vec4f;
typedef Vector<int, 3> Vec3i;
typedef Vector<int, 3> Vec3i;

#include "vector_impl.tpp"

}  // namespace gem
