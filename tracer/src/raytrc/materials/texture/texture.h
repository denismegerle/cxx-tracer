/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Textures save information and properties and can then apply them on
 * intersections and the intersection materials, given the uv coordinate.
 * Different types of textures can thus change different values of the
 * intersection, such as the normal or the material and surface characteristics.
 */
class Texture {
 public:
  /*!
   * @brief Applies its texture at the given uv coordinate onto the
   * intersection.
   * @param intersection interesction with valid parameters
   * @param uv uv coordinate of intersection point on the texture (non-wrapped)
   * @param dudv not specified yet, used for trilinear filtering
   */
  virtual void applyOn(Intersection *intersection, Vec2f uv,
                       Vec2f dudv = Vec2f(0.0f)) const = 0;
};

}  // namespace raytrc