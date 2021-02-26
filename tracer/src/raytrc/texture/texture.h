#pragma once

#include "maths/maths.h"

using namespace gem;

namespace raytrc {

class Texture {
 public:
  virtual Vec3f evaluate(Vec2f uv,
                         Vec2f dudv = Vec2f(0.0f)) const = 0;
};

}  // namespace raytrc