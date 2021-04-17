/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "light_source.h"
#include "maths/maths.h"

using namespace gem;

namespace raytrc {

/*!
 * More complex and stochastic light calcuation: Light is modeled as a spherical
 * source, thus shadow rays can partly reach and partly not reach the light,
 * generating soft shadows.
 */
class SphereLight : public LightSource {
 public:
  float radius; /*!< radius of light, defining soft shadow strength */
  Vec3f diffuse, specular; /*!< light component intensities in RGB */

  /*!
   * @brief Convenience constructor for spherical light
   * @param position of light
   * @param radius of light, defining soft shadow strength
   * @param intensity of light, same for all components
   */
  SphereLight(Vec3f position, float radius, Vec3f intensity)
      : LightSource(position),
        radius(radius),
        diffuse(intensity),
        specular(intensity){};

  /*!
   * @brief Constructor for each intensity component separately
   */
  SphereLight(Vec3f position, float radius, Vec3f diffuse, Vec3f specular)
      : LightSource(position),
        radius(radius),
        diffuse(diffuse),
        specular(specular){};

  /*!
   * @brief See implementation, computes RGB by stochastically integrating over
   * many (random) shadow rays from the intersection point to random points on a
   * disc (on the light source)
   * @param world scene
   * @param intersection intersection with parameters
   * @return RGB light at intersection point
   */
  Vec3f computeDirectLight(World *world, Intersection *intersection);
};

}  // namespace raytrc
