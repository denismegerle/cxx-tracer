// tracer.cpp : Defines the entry point for the application.

#include "tracer.h"
#include "maths/maths.h"
#include "maths/vector.h"
#include "maths/matrix.h"

#include <array>
#include <iostream>

using namespace std;

int main() {
  std::cout << "Maths version is " << MATHS_VERSION << std::endl;

  std::array<float, 4> arr = {0.1f, 0.2f, 0.3f, 0.4f};
  std::array<float, 4> arr2 = {0.2f, 0.3f, 0.4f, 0.5f};
  std::array<float, 3> arr3 = {0.0f, 0.1f, 0.2f};
  std::array<float, 3> arr4 = {0.2f, 0.4f, 0.6f};


  gem::Vec3f vec3(arr3);
  gem::Vec3f vec4(arr4);

  gem::Vector<float, 4> vec(arr);
  gem::Vector<float, 4> vec2(arr2);

  std::array<std::array<float, 3>, 3> arr2d1 = {5, 8, 2, 8, 3, 1, 5, 3, 9};
  gem::Matrix<float, 3> mat1(arr2d1);
  std::array<std::array<float, 3>, 3> arr2d2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  gem::Matrix<float, 3> mat2(arr2d2);

  std::cout << (vec + vec2).mult(2.0f) << std::endl;
  std::cout << vec * 2.0f << std::endl;
  std::cout << vec3 * vec4 * 2.0f << std::endl;
  std::cout << vec3.norm(gem::Vector<float, 3>::NormType::MAX) << std::endl;

  std::cout << mat1 + mat2 << std::endl;
  std::cout << mat1 * 2.0f << std::endl;
  std::cout << mat1.dot(mat2) << std::endl;
  std::cout << mat1.dot(vec3) << std::endl;
  std::cout << mat1.transpose() << std::endl;

  return 0;
}