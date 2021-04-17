/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

/*!
 * @brief Spherical Mapping maps a circular picture as a sphere.
*/
class SphericalMapping : public TextureMapping {
 public:
  /*!
   * @brief uv coordinate calcuation according to OpenGLs spherical maps
   * @param intersection intersection with parameters
   * @return uv coordinates
  */
  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc