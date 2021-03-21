#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"
#include "object_base.h"

#include "raytrc/geometry/objects/aabb.h"

using namespace gem;

namespace raytrc {

class Sphere : public ObjectBase {
 public:
  float radius;

  Sphere(){};
  Sphere(Vec3f position, float radius) : ObjectBase(position), radius(radius){};

  bool intersect(Ray *ray, Intersection *intersection) override;
  AABB getAABB() override;
};

}  // namespace raytrc