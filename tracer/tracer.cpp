// tracer.cpp : Defines the entry point for the application.

#include "tracer.h"

#include <omp.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/cameras/pinhole_camera.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/objects/plane.h"
#include "raytrc/geometry/objects/sphere.h"
#include "raytrc/geometry/ray.h"
#include "raytrc/light/ambient_light.h"
#include "raytrc/light/point_light.h"
#include "raytrc/world.h"
#include "stb_image_write.h"

constexpr auto PIXEL_WIDTH = 1920;
constexpr auto PIXEL_HEIGHT = 1080;
constexpr auto CHANNEL = 3;
constexpr auto N_SUPERSAMPLES = 10;
constexpr auto SUPERSAMPLING_VARIANCE = 1.0f;
constexpr auto REFLECTION_ON = true;
constexpr auto TRANSMISSION_ON = true;
constexpr auto MAX_RECURSION_DEPTH = 3;

using namespace std;
using namespace raytrc;
using namespace gem;

Vec3f raytrace(World *world, Ray *ray, int recursionDepth,
               int maxRecursionDepth);
float gamma_correct(float color, float gamma);

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

- make light source emit ambient, specular, diffuse light and use in phong
calculation
*/

int main() {
  /* ********** CAMERA CREATION ********** */
  Vec3f camPosition(-4.0f, 0.0f, 3.0f);
  Vec3f camTarget(-2.0f, 0.0f, 2.0f);
  Vec3f camUp(0.0f, 0.0f, 1.0f);
  float camDistanceToImagePane = 0.25f;
  PinholeCamera cam(camPosition, camTarget, camUp, PIXEL_WIDTH, PIXEL_HEIGHT,
                    camDistanceToImagePane);

  /* ********** WORLD CREATION ********** */
  std::vector<shared_ptr<ObjectBase>> objects;
  std::vector<shared_ptr<LightSource>> lightSources;

  objects.push_back(make_shared<Sphere>(Vec3f(-2.0f, 0.0f, 2.0f),
                                        &Materials::GLASS_SIMPLE,
                                        0.5f * tan(M_PI / 4.0f)));
  objects.push_back(make_shared<Sphere>(
      Vec3f(-2.0f, -2.0f, 2.0f), &Materials::BRONZE, 0.5f * tan(M_PI / 4.0f)));
  objects.push_back(make_shared<Sphere>(
      Vec3f(-2.0f, 2.0f, 2.0f), &Materials::GOLD, 0.5f * tan(M_PI / 4.0f)));

  objects.push_back(make_shared<Plane>(Vec3f(0.0f, 0.0f, 0.0f),
                                       &Materials::WHITE_RUBBER,
                                       Vec3f(0.0f, 0.0f, 1.0f)));
  objects.push_back(make_shared<Plane>(Vec3f(0.0f, 0.0f, 0.0f),
                                       &Materials::REFLECTIVE_SIMPLE,
                                       Vec3f(-1.0f, 0.0f, 0.0f)));
  objects.push_back(make_shared<Plane>(Vec3f(5.0f, 0.0f, 0.0f),
                                       &Materials::WHITE_RUBBER,
                                       Vec3f(1.0f, 0.0f, 0.0f)));
  objects.push_back(make_shared<Plane>(Vec3f(0.0f, 0.0f, 6.0f),
                                       &Materials::WHITE_RUBBER,
                                       Vec3f(0.0f, 0.0f, -1.0f)));

  lightSources.push_back(make_shared<PointLight>(
      Vec3f(-4.0f, 2.0f, 5.0f), Vec3f(2.0f), Vec3f(2.0f), Vec3f(3.0f)));

  World world(&cam, objects, lightSources);

  /* ********** RT CODE ********** */
  uint8_t *frameBuffer = new uint8_t[CHANNEL * PIXEL_WIDTH * PIXEL_HEIGHT];

#pragma omp parallel for
  for (int y = 0; y < PIXEL_HEIGHT; y++) {
    for (int x = 0; x < PIXEL_WIDTH; x++) {
      Vec3f color(0.0f);
      for (int i = 0; i < N_SUPERSAMPLES; i++) {
        /* 1. GENERATE PRIMARY RAY FOR THIS PIXEL */
        Ray primaryRay = cam.generateRay(x, y, SUPERSAMPLING_VARIANCE);

        // raytrace recursively
        color =
            color + (1.0f / N_SUPERSAMPLES) *
                        raytrace(&world, &primaryRay, 0, MAX_RECURSION_DEPTH);

        for (int c = 0; c < CHANNEL; c++) {
          if (color.norm() != 0.0f) {
            frameBuffer[c * PIXEL_WIDTH * PIXEL_HEIGHT + y * PIXEL_WIDTH + x] =
                (uint8_t)(gamma_correct(color[c], 1.0f) * 255.0f);
          } else {
            frameBuffer[c * PIXEL_WIDTH * PIXEL_HEIGHT + y * PIXEL_WIDTH + x] =
                0;
          }
        }
      }
    }
  }

  cimg_library::CImg<uint8_t> cimage(frameBuffer, PIXEL_WIDTH, PIXEL_HEIGHT, 1,
                                     CHANNEL);
  cimg_library::CImgDisplay disp;
  disp.display(cimage).resize(false).move(100, 100).wait(20000);
  cimage.save("raytraced.png");

  delete[] frameBuffer;
  return 0;
}

Vec3f raytrace(World *world, Ray *ray, int recursionDepth,
               int maxRecursionDepth) {
  Vec3f color(0.0f);

  // recursion stop condition
  if (recursionDepth > maxRecursionDepth) return color;

  /* 2. CALCULATE INTERSECTION OF RAY WITH (FIRST) WORLD OBJECT */
  Intersection i;
  if (!world->cast(ray, &i)) return color;

  /* 3. CALCULATE LIGHT AND SHADING */
  // direct light from the light sources
  for (auto light : world->lightSources) {
    color = color + light->computeDirectLight(world, &i);
  }

  // reflection rays, only if material is actually reflective
  if (i.material->kr.norm() > 0.0f &&
      REFLECTION_ON) {  // TODO change to isReflective method
    Ray reflect = ray->reflect(&i);
    color =
        color + i.material->kr.mult(raytrace(
                    world, &reflect, recursionDepth + 1, maxRecursionDepth));
  }

  if (i.material->kt.norm() > 0.0f && TRANSMISSION_ON) {
    // for simplification, the assumption is: we either enter or leave a
    // material (from/to air)
    float theta_i_ = acos(ray->direction.normalize().dot(i.normal));
    float theta_i = (theta_i_ > M_PI / 2.0f) ? M_PI - theta_i_ : theta_i_;
    bool entering = theta_i_ > M_PI / 2.0f;

    float eta_1 = entering ? Materials::AIR.eta : i.material->eta;
    float eta_2 = entering ? i.material->eta : Materials::AIR.eta;
    Vec3f kt = entering ? i.material->kt : Materials::AIR.kt;

    // TIR if eta_1 > eta_2 ^ asin(eta_2 / eta_1) < theta_i
    if (eta_1 < eta_2 ||
        asin(eta_2 / eta_1) >
            theta_i) {  // if eta_1 > eta_2 total internal reflection can occur
      Ray refract = ray->refract(&i, eta_1, eta_2);

      color = color + kt.mult(raytrace(world, &refract, recursionDepth + 1,
                                       maxRecursionDepth));
    }
  }

  color = color.clamp(Vec3f(0.0f), Vec3f(1.0f));
  return color;
}

float gamma_correct(float color, float gamma) {
  return min(1.0f, pow(color, 1.0f / gamma));
}