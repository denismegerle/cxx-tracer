/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/material.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief This class models a ray with origin and direction vector. Also saves
 * current state t on the ray that can be updated in other methods.
 */
struct Ray {
  Vec3f origin;    /*!< origin position in world space */
  Vec3f direction; /*!< direction vector in world space */
  float t;         /*!< temporary position on ray */

  /*!
   * @brief Generation of a ray via origin and direction, direction will not be normalized.
   * @param origin origin in world space
   * @param direction direction in world space
  */
  Ray(Vec3f origin, Vec3f direction)
      : origin(origin), direction(direction), t(0.0f){};

  /*!
   * @brief Equates the vector at t.
   * @return Position (on the vector) at t, i.e. o + td
  */
  Vec3f equate();
  /*!
   * @brief Reflecting the vector on an intersection (which provides the reflection position and normal)
   * @param intersection with position and normal
   * @return reflected ray
  */
  Ray reflect(Intersection* intersection);
  /*!
   * @brief Refracting the vector on an intersection, here we need the refraction indices (eta1, eta2) of the two media.
   * @param intersection intersection with position and normal
   * @param eta_1 refraction index of origin medium
   * @param eta_2 refraction index of destination medium
   * @return refracted ray
  */
  Ray refract(Intersection* intersection, const float eta_1, const float eta_2);
};

}  // namespace raytrc