/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"
#include "object_base.h"

#include "raytrc/geometry/bounding_volumes/aabb.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Sphere defined by radius and position
*/
class Sphere : public ObjectBase {
 public:
  float radius; /*!< radius of sphere */

  /*!
   * @brief Initialization via position and radius, const
   * @param position sphere center in world space
   * @param radius radius of sphere
  */
  Sphere(Vec3f position, float radius) : ObjectBase(position), radius(radius){};

  /*!
   * @brief Intersection test based on
   * @link{https://www.iquilezles.org/www/articles/intersectors/intersectors.htm}
   */
  bool intersect(Ray *ray, Intersection *intersection) override;
  AABB getAABB() override;
};

}  // namespace raytrc