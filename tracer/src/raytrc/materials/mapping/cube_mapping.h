#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

class CubeMapping : public TextureMapping {
 public:
  Vec2f scale;

  CubeMapping(Vec2f scale) : scale(scale){};

  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc