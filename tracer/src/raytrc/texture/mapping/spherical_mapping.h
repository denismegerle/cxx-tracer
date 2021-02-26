#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/texture/mapping/texture_mapping.h"

namespace raytrc {

class SphericalMapping : TextureMapping {
  Vec2f scale;
  Vec3f center;

  SphericalMapping(Vec3f center, Vec2f scale) : center(center), scale(scale){};

  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc