#pragma once

#include "maths/maths.h"

namespace raytrc {

class PointLight : public LightSource {
  gem::Vec3f pos, I_L;  // pos + intensity (rgb)
};

}
