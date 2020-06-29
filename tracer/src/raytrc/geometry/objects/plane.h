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
  Plane(Vec3f position, Material *material, Vec3f normal)
      : ObjectBase(position, material), normal(normal.normalize()){};

  bool intersect(Ray *ray, Intersection *intersection);
};

}  // namespace raytrc