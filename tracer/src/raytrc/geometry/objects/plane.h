#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"
#include "object_base.h"

using namespace gem;

namespace raytrc {

class Plane : public ObjectBase {
 public:
  Vec3f normal;

  Plane(){};
  Plane(Vec3f position, Vec3f normal)
      : ObjectBase(position), normal(normal.normalize()){};

  bool intersect(Ray *ray, Intersection *intersection) override;
};

}  // namespace raytrc