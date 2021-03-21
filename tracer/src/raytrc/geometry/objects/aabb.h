#pragma once

#include "maths/maths.h"

#include "raytrc/geometry/ray.h"

namespace raytrc {

struct AABB {
 public:
  Vec3f min, max;

  AABB(){};
  AABB(Vec3f min, Vec3f max) : min(min), max(max){};

  AABB combine(AABB other);  // i.e. union
  uint8_t getMaxDimension();
  bool AABB::intersect(Ray *ray);

} typedef AABB;

}
