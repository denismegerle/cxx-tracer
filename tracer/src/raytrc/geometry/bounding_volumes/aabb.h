/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

/*!
 * @brief Axis aligned bounding box as a bounding volume for objects.
 */
struct AABB {
 public:
  Vec3f min; /*!< x, y, z min */
  Vec3f max; /*!< x, y, z max */

  /*!
   * @brief Default initializing AABBs, i.e. to world center
   */
  AABB() = default;

  /*!
   * @brief Initialization with x,y,z min and x,y,z max
   * @param min min values of BB
   * @param max max values of BB
   */
  AABB(Vec3f min, Vec3f max) : min(min), max(max){};

  /*!
   * @brief Combining two AABBs (self with other). Simply choosing min/max per
   * dimension.
   * @param other other AABB
   * @return new instance of an AABB, combined version of the two inputs
   */
  AABB combine(AABB other);  // i.e. union

  /*!
   * @brief Gets the maximum dimension of an AABB.
   * @return 0, 1, 2 respective x, y, z
   */
  uint8_t getMaxDimension();

  /*!
   * @brief Fast intersection test for a ray in world space against this AABB
   * @param ray ray to be tested
   * @return whether intersection found, does not change ray
   */
  bool AABB::intersect(Ray *ray);

} typedef AABB;

}  // namespace raytrc
