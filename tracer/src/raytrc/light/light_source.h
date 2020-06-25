#pragma once

/*

light source + point light here

*/
#include "maths/maths.h"

#include "raytrc/geometry/intersection.h"

namespace raytrc {

class World;
// TODO add lightsource AMBIENTLIGHT, that simply adds val to each pixel (for convenience)
class LightSource {
 public:
  virtual Vec3f computeDirectLight(World *world, Intersection *intersection) = 0;
};

}  // namespace raytrc