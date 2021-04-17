/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

/*!
 * @brief Zero mapping maps all points to zero in the texture space.
 */
class ZeroMapping : public TextureMapping {
 public:
  ZeroMapping(){};

  /*!
   * @brief Zero for all points
   */
  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc