#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

namespace raytrc {

class TextureMapping {
 public:
  virtual Vec2f get_uv(Intersection *intersection) const = 0;
};

}
