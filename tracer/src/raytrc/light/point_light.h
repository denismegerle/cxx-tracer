#pragma once

#include "maths/maths.h"
#include "light_source.h"

using namespace gem;

namespace raytrc {

class PointLight : public LightSource {
 public:
  Vec3f position, intensity;  // pos + intensity I_L (rgb)

  PointLight(Vec3f position, Vec3f intensity)
      : position(position), intensity(intensity){};

  Vec3f computeDirectLight(Intersection *intersection);
};

}
