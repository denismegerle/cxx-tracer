#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"
#include "material.h"

using namespace gem;

namespace raytrc {

class ObjectBase {
 public:
  Vec3f position;
  const Material *material;

  ObjectBase(){};
  ObjectBase(Vec3f position, const Material *material) : position(position), material(material){};

  /* calculates closest intersection in positive direction */
  virtual bool intersect(Ray *ray, Intersection *intersection) = 0;
};

}