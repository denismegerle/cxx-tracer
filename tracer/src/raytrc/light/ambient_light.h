/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "light_source.h"
#include "maths/maths.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief An ambient light models constant light throughout a scene.
 */
class AmbientLight : public LightSource {
 public:
  Vec3f intensity; /*!< intensity of light for RGB */

  /*!
   * @brief Constructor for ambient light only needs position and intensity
   * (RGB)
   * @param position of light
   * @param intensity of light in RGB
   */
  AmbientLight(Vec3f position, Vec3f intensity)
      : LightSource(position), intensity(intensity){};

  /*!
   * @brief Calculation according to light intensity, equally for each point in
   * the scene.
   */
  Vec3f computeDirectLight(World *world, Intersection *intersection);
};

}  // namespace raytrc
