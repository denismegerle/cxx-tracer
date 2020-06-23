#pragma once

#include "maths/maths.h"

using namespace gem;

namespace raytrc {

class Ray {
 public:
  Vec3f origin, direction;
  float t;
  void* intersectedObject;

  Ray(){};
  Ray(Vec3f origin, Vec3f direction) : origin(origin), direction(direction){};

  Vec3f equate();
};

}  // namespace raytrc