/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/materials/material.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Intersection contains metadata for each intersection, such as the
 * object, material properties (for light calculation) and position/normal.
 */
struct Intersection {
  Vec3f position;     /*!< intersection position, beware of rounding errors */
  Vec3f normal;       /*!< intersection normal */
  Vec3f negRayVector; /*!< vector in the opposite direction of the ray */

  Material material; /*!< new instance of material, can be altered for each
                        intersection by textures and the intersected object */
  void* intersectedObject = nullptr; /*!< can only be written externally
                              (intersect methods) */

  /*!
   * @brief Default intersection to use as a stub for the intersect methods.
   * Don't need other constructors since data is set through intersect methods
   * instead, only if needed.
   */
  Intersection() = default;
};

}  // namespace raytrc