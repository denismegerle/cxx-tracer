#pragma once

#include "intersection.h"
#include "maths/maths.h"
#include "objects/material.h"

using namespace gem;

namespace raytrc {

class Ray {
 public:
  Vec3f origin, direction;
  float t;

  Ray(){};
  Ray(Vec3f origin, Vec3f direction) : origin(origin), direction(direction){};

  Vec3f equate();
  Ray reflect(Intersection* intersection);
  Ray Ray::refract(Intersection* intersection, const float eta_1,
                   const float eta_2);
};

}  // namespace raytrc