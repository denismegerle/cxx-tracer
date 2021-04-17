/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "object_base.h"
#include "raytrc/geometry/bounding_volumes/aabb.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Triangle definition by its corner points, position in the middle.
 */
class Triangle : public ObjectBase {
 public:
  Vec3f v0, v1, v2; /*!< three corner points */

  /*!
   * @brief Generating a triangle by its edge points, position defined as average of corners
   * @param v0 edge point
   * @param v1 edge point
   * @param v2 edge point
  */
  Triangle(Vec3f v0, Vec3f v1, Vec3f v2)
      : ObjectBase((1.0f / 3.0f) * (v0 + v1 + v2)), v0(v0), v1(v1), v2(v2){};

  /*!
   * @brief Intersection test based on
   * @link{https://www.iquilezles.org/www/articles/intersectors/intersectors.htm}
   */
  bool intersect(Ray *ray, Intersection *intersection) override;
  AABB getAABB() override;
};

}  // namespace raytrc