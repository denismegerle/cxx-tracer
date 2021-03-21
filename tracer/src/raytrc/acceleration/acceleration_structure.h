#pragma once

#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

class AccelerationStructure {
 public:
  virtual bool cast(Ray *ray, Intersection *intersection) = 0;
};

}  // namespace raytrc
