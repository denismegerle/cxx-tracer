#pragma once

#include "maths/maths.h"
#include "object_base.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/aabb.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

class Triangle : public ObjectBase {
 public:
  Vec3f v0, v1, v2;

  Triangle(){};
  Triangle(Vec3f v0, Vec3f v1, Vec3f v2)
      : ObjectBase((1.0f / 3.0f) * (v0 + v1 + v2)), v0(v0), v1(v1), v2(v2) {};

  bool intersect(Ray *ray, Intersection *intersection) override;
  AABB getAABB() override;
};

}  // namespace raytrc