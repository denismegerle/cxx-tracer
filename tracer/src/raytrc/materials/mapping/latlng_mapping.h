/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

/*!
 * @brief Mapping a rectangular picture onto a sphere, somewhat like the
 * Mercatur projection. Introduces distortions and does not have equal
 * distribution of sample points.
 */
class LatLngMapping : public TextureMapping {
 public:
  Vec2f scale; /*!< scale for projection */

  /*!
   * @brief Standard constructor with scale for projection
   * @param scale defining how large the projection is
  */
  LatLngMapping(Vec2f scale) : scale(scale){};

  /*!
   * @brief LatLng projection can be done according to sphere coordinates (equirectangular)
   * @param intersection intersection with parameters
   * @return uv coordinates, since we use a standard projection onto a sphere always in [0, 1]
  */
  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc