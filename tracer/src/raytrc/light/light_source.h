/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

namespace raytrc {

/* forward declaration to avoid circular dependencies */
class World;

/*!
 * @brief Light sources can compute direct light onto any intersection and thus
 * provide RGB feedback for a certain spot in the scene, given this light.
 */
class LightSource {
 public:
  Vec3f position; /*!< position of the light */

  /*!
   * @brief Convenience constructor for light sources
   * @param position central position of the light
  */
  LightSource(Vec3f position) : position(position){};

  /*!
   * @brief Returns RGB values based on an intersection and the position and
   * properties of this light
   * @param world world to compute in (scene)
   * @param intersection intersection with position, normal and material
   * properties
   * @return RGB vector
   */
  virtual Vec3f computeDirectLight(World *world,
                                   Intersection *intersection) = 0;
};

}  // namespace raytrc