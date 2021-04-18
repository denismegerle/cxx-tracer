/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "plane.h"

#include "raytrc/geometry/bounding_volumes/aabb.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"

using namespace raytrc;

/*!
 * Closest intersection point, this is the simplest (non-optimized) intersection
 * test for rays and planes, derived by plugging the ray into implicit
 * definition of planes.
 */
bool Plane::intersect(Ray *ray, Intersection *intersection) {
  float relativeOrientation =
      ray->direction.normalize() * this->normal;  // normal already normalized

  if (relativeOrientation != 0) {  // not parallel -> definitely intersecting,
                                   // case parallel + inf intersections ignored.
    float t = (this->normal * this->position - ray->origin * this->normal) /
              relativeOrientation;  // = (d - E * N) / (D * N)

    ray->t = t / ray->direction.norm();

    intersection->intersectedObject = this;
    intersection->position = ray->equate();
    intersection->normal = ((ray->origin - this->position) * this->normal > 0)
                               ? this->normal.normalize()
                               : -1.0f * this->normal.normalize();
    intersection->negRayVector =
        (ray->origin - intersection->position).normalize();

    return true;
  }
  return false;
}

/*!
 * Planes have an infinite expansion, using zero AABBs to make sure they do not
 * destroy AABB based acceleration structures.
 */
AABB Plane::getAABB() { return AABB(Vec3f(-FLT_MAX), Vec3f(+FLT_MAX)); };