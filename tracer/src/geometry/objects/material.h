#pragma once

#include "maths/maths.h"

namespace raytrc {

class Material {  // reflection parameter + phong exponent
  gem::Vec3f ka, kd, ks;
  float n;
};

}  // namespace raytrc