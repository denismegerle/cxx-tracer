/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

namespace raytrc {

/*!
 * @brief Texture mappings map the given point of an object (relative to that
 * object) onto a texture (i.e. image).
 */
class TextureMapping {
 public:
  /*!
   * @brief Get the uv coordinates (relative texture coordinates). These can be
   * any float, but 0 means (top, left) of the texture, 1 (bottom, right), and
   * depending on the wrap mode values outside [0,1] are defined differently.
   * @param intersection intersection with parameters and material
   * @return uv coordinates on the texture, given this mapping
   */
  virtual Vec2f get_uv(Intersection *intersection) const = 0;
};

}  // namespace raytrc
