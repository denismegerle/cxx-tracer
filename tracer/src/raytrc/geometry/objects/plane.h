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
 * @brief Simple plane (inf expansion) in space
 */
class Plane : public ObjectBase {
 public:
  Vec3f normal; /*!< plane normal, defines refraction/transmission direction! */

  /*!
   * @brief Plane constructor defined by position and normal, normal will be
   * normalized and saved
   * @param position any point on the plane
   * @param normal not necessarily normalized normal
   */
  Plane(Vec3f position, Vec3f normal)
      : ObjectBase(position), normal(normal.normalize()){};

  /*!
   * @brief Intersection test based on
   * @link{https://www.iquilezles.org/www/articles/intersectors/intersectors.htm}
   */
  bool intersect(Ray *ray, Intersection *intersection) override;
  AABB getAABB() override;
};

}  // namespace raytrc