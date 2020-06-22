// tracer.cpp : Defines the entry point for the application.

#include "tracer.h"

#include <array>
#include <fstream>
#include <iostream>

#include "CImg.h"
#include "maths/maths.h"
#include "src/geometry/objects/object_base.h"
#include "src/geometry/ray.h"
#include "stb_image_write.h"

using namespace std;
using namespace raytrc;
using namespace gem;

void test_main(void);

typedef struct PinholeCamera {
  // TODO: actual class + normalize input vectors through constructor!
  Vec3f position,
      imagePaneNormal;  // pos + normal that points away from image pane
  float focalLength;    // || pane - position ||
  int width, height;    // width, height of image pane
} Camera;

/*
TODO:
- create simple maths library and allow for use here
- create objects (Ray, Intersection, ...) from the lecture
- parser for input of scenes + output of png files!
- parser to input material types + their parameters!
- open png after prg finish
- simple whitted style raytracing!
X shaders to use gpu? (nah)

*/

int main() {
  /* TODO NEXT:
    - create camera, sphere, plane stub objects
  */
  Camera cam;
  cam.width = 500;
  cam.height = 500;
  cam.focalLength = 100;
  cam.position = Vec3f(0.0f);
  cam.imagePaneNormal = Vec3f();

  return 0;
}

/*

vec3 raytrace( Ray *ray, ... ) {
vec3 color = 0.0f;

Intersection i;
if ( !cast( ray, FLOAT_MAX, &i ) )
return color;

for ( jede Lichtquelle )
color += computeDirectLight( ... );
if ( Fläche ist spiegelnd ) {
// berechne Reflexionsstrahl
Ray reflect = ...;
color += i.kr * raytrace( reflect, ... );
}
if ( Fläche ist (semi-)transparent ) {
// berechne Transmissionsstrahl
Ray refract = ...;
if ( Totalreflexion )
color += i.kr * raytrace( reflect, ... );
else
color += i.kt * raytrace( refract, ... );
}
return color;
}

================================

RAY CLASS -> needs generation of ray, casting of ray
MATERIAL CLASS -> also implements different base materials statically, kinda
like enums? INTERSECTION CLASS -> intersection LIGHTSOURCE, POINTLIGHT -> needs
abstract computeDirectLight

TODO
OBJECT -> base of objects, needs abstract intersect(ray) method
SPHERE
PLANE
CUBE (?)
================================

for ( y = 0; y < height; y++ ) {
for ( x = 0; x < width; x++ ) {

HERE TO
u = l + (r-l) * (x+0.5) / width;
v = t + (b-t) * (y+0.5) / height;
s = ...;
d = normalize( s );
HERE IS ACTUALLY RAY CASTING (GENERATE RAY(Ray *ray, int x, int y))

HERE TO
// finde nächsten Schnittpunkt
intersection = NULL;
float t = FLOAT_MAX;
for ( each object ) {
t‘ = intersect( object, e, d );
if ( t‘ > 0 && t‘ < t ) {
intersection = object;
t = t‘;
} }
// Beleuchtungsberechnung
if ( intersection != NULL ) {
computeDirectLight ...
}
HERE IS ACTUALLY RAYTRACE(...)!

} }

===============================

bool cast(Ray *ray, float maxDist)  {
// finde nächsten Schnittpunkt
intersection = NULL;
float t = FLOAT_MAX;
for ( each object ) {
t‘ = intersect( object, e, d );
if ( t‘ > 0 && t‘ < t ) {
intersection = object;
t = t‘;
} }
}

=======================================

compute direct light (light -> obj) with shadows...

vec3 PointLight::computeDirectLight( const Intersection &i, ... ) {
// ambienter Term
vec3 I = i.material->ka * I_L;
vec3 L = pos - i.p;
// Schattenstrahl
float dist2Light = length( L );
for ( each object ) {
t‘ = intersect( object, i.p, L );
if ( t‘ > 0 && t‘ < dist2Light )
return I;
}
...
};

=====================================

direct light computation with phong lightning model

vec3 PointLight::computeDirectLight( const Intersection &i, ... )
{
// ambienter Term
vec3 I = i.material->ka * I_L;
// hier: Punktlichtquelle
vec3 L = normalize( pos - i.p );
float NdotL = dot( i.n, L );
if ( NdotL > 0 ) {
// diffuser Term
I += i.material->kd * I_L * NdotL;
// spekularer Term
vec3 R = 2.0f * i.n * NdotL – L;
float RdotV = dot( R, V );
if ( RdotV > 0 ) {
I += i.material->ks * I_L * powf( RdotV, i.material->n );
}
}
};

======================================

*/

void test_main(void) {
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

  const char *filename = "myfile.bmp";

  uint8_t data[7500] = {255};

  stbi_write_bmp(filename, 50, 50, 3, &data);

  cimg_library::CImg<uint8_t> cimage(data, 50, 50, 1, 3);
  cimg_library::CImgDisplay disp;
  disp.display(cimage).resize(false).move(100, 100).wait(5000);
}