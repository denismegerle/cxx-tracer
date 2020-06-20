#pragma once

#include "maths/maths.h"
#include "src/geometry/objects/material.h"

namespace raytrc {

class Intersection {
  gem::Vec3f p, n, v;  // pos, normale, vector to origin of ray
  Material *material;
};

}  // namespace raytrc