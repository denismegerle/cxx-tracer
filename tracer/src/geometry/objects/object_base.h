#pragma once

#include "maths/maths.h"
#include "src/geometry/intersection.h"
#include "src/geometry/ray.h"

using namespace gem;

namespace raytrc {

class ObjectBase {
 public:
  Vec3f position;

  virtual Intersection intersect(Ray *ray) = 0;
};

}