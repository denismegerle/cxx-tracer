/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "light_source.h"
#include "maths/maths.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief A point light is a dimension-less point emitting light equally in all
 * directions, the lighting model used is the standard phong model.
 */
class PointLight : public LightSource {
 public:
  Vec3f diffuse, specular; /*!< diffuse and specular light intensity */

  /*!
   * @brief Convenience constructor for same intensity in diffuse / specular
   * part
   * @param position light position
   * @param intensity light intensity
   */
  PointLight(Vec3f position, Vec3f intensity)
      : LightSource(position), diffuse(intensity), specular(intensity){};

  /*!
   * @brief Initialization of light with different diffuse / specular component
   * @param position position of light
   * @param diffuse component intensity in RGB
   * @param specular component intensity in RGB
   */
  PointLight(Vec3f position, Vec3f diffuse, Vec3f specular)
      : LightSource(position), diffuse(diffuse), specular(specular){};

  /*!
   * @brief Calculation of light on intersected point, according to phong model
   * without the ambient term.
   * @param world scene
   * @param intersection intersection with parameters
   * @return RGB light at intersection point
   */
  Vec3f computeDirectLight(World *world, Intersection *intersection);
};

}  // namespace raytrc
