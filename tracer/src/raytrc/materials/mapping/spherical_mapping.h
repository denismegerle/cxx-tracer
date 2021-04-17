/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

class SphericalMapping : public TextureMapping {
 public:
  SphericalMapping(){};

  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc