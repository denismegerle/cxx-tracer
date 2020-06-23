// tracer.cpp : Defines the entry point for the application.

#include "tracer.h"

#include <array>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/cameras/pinhole_camera.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"
#include "raytrc/world.h"
#include "raytrc/geometry/objects/sphere.h"

#include "stb_image_write.h"

using namespace std;
using namespace raytrc;
using namespace gem;

void test_main(void);

/*
TODO:
- create simple maths library and allow for use here
- create objects (Ray, Intersection, ...) from the lecture
- parser for input of scenes + output of png files!
- parser to input material types + their parameters!
- open png after prg finish
- simple whitted style raytracing!
X shaders to use gpu? (nah)
- restrict cast to certain max length with parameter!

*/

int main() {
  Vec3f camPosition(0.0f, 0.0f, 0.0f);
  Vec3f camTarget(1.0f, 0.0f, 0.0f);
  Vec3f camUp(0.0f, 0.0f, 1.0f);
  int width = 1920;
  int height = 1080;
  float camDistanceToImagePane = 1.0f;
  PinholeCamera cam(camPosition, camTarget, camUp, width, height,
                    camDistanceToImagePane);
  std::vector<ObjectBase *> objects;
  std::vector<LightSource *> lightSources;

  objects.push_back(new Sphere(Vec3f(2.0f, 0.0f, 0.0f), nullptr, 0.5f * tan(M_PI / 4.0f)));

  World world(&cam, objects, lightSources);
  
  uint8_t *frameBuffer = (uint8_t*) malloc(1920 * 1080);
  if (!frameBuffer) {
    std::cout << "MEM ALLOC FAILED" << std::endl;
    return -1;
  }

  #pragma omp parallel for
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      frameBuffer[y * 1920 + x] = 0;

      /* 1. GENERATE PRIMARY RAY FOR THIS PIXEL */
      Ray primaryRay = cam.generateRay(x, y);
      Vec3f normalizedRayDirection = primaryRay.direction.normalize();

      Intersection i;
      if (world.cast(&primaryRay, &i)) {
        frameBuffer[y * 1920 + x] = 255;
      }
    }
  }

  cimg_library::CImg<uint8_t> cimage(frameBuffer, 1920, 1080, 1, 1);
  cimg_library::CImgDisplay disp;
  disp.display(cimage).resize(false).move(100, 100).wait(10000);

  free(frameBuffer);
  return 0;
}

Vec3f raytrace(World *world, Ray *ray, int recursionDepth) {
  Vec3f color(0.0f);

  /* 2. CALCULATE INTERSECTION OF RAY WITH (FIRST) WORLD OBJECT */
  Intersection i;

  return Vec3f();
}
/*

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