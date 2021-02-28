#pragma once

#include "maths/maths.h"

#include "raytrc/geometry/intersection.h"

using namespace gem;

namespace raytrc {

class Texture {
 public:
  virtual void applyOn(Intersection *intersection, Vec2f uv,
                         Vec2f dudv = Vec2f(0.0f)) const = 0;
};

}  // namespace raytrc