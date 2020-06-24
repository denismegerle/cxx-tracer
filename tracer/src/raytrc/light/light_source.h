#pragma once

/*

light source + point light here

*/
#include "maths/maths.h"

#include "raytrc/geometry/intersection.h"

namespace raytrc {

class LightSource {
 public:
  virtual Vec3f computeDirectLight(Intersection *intersection) = 0;
};

}  // namespace raytrc