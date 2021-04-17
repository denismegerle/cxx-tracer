/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

class PlanarMapping : public TextureMapping {
 public:
  Vec3f position;
  Vec2f scale;
  Vec3f s_axis, t_axis;

  PlanarMapping(Vec3f position, Vec2f scale, Vec3f s_axis, Vec3f t_axis)
      : position(position), scale(scale), s_axis(s_axis), t_axis(t_axis){};

  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc