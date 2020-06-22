#pragma once

#include "maths/maths.h"
#include "src/geometry/objects/object_base.h"
#include "src/geometry/intersection.h"
#include "src/geometry/ray.h"

using namespace gem;

namespace raytrc {

class Plane : public ObjectBase {
 public:
  Vec3f normal;

  Intersection intersect(Ray *ray);
};

}  // namespace raytrc