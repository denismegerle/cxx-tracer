/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "sphere.h"

#include "raytrc/geometry/bounding_volumes/aabb.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"

using namespace raytrc;

/*!
 * Closest intersection point of the ray returned, can find non, one (tangent
 * intersection) or two intersections.
 */
bool Sphere::intersect(Ray *ray, Intersection *intersection) {
  float a = ray->direction * ray->direction;
  float b = 2.0f * ray->direction * (ray->origin - this->position);
  float c = (ray->origin - this->position) * (ray->origin - this->position) -
            this->radius * this->radius;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) return false;

  float t = FLT_MAX;
  if (discriminant == 0) {
    t = -b / (2 * a);
    if (t <= 0) return false;
  } else {
    float t1 = (-b + sqrt(discriminant)) / (2 * a);
    float t2 = (-b - sqrt(discriminant)) / (2 * a);

    if (t1 <= 0 && t2 <= 0) return false;
    t = (t1 > 0 && t2 > 0) ? ((t1 < t2) ? t1 : t2) : ((t1 > 0) ? t1 : t2);
  }

  ray->t = t;

  intersection->intersectedObject = this;
  intersection->position = ray->equate();
  intersection->normal = (intersection->position - this->position).normalize();
  intersection->negRayVector =
      (ray->origin - intersection->position).normalize();

  return true;
}

/*!
 * AABB min = pos - rad, max = pos + rad (for each dimension)
 */
AABB Sphere::getAABB() {
  return AABB(position - Vec3f(radius), position + Vec3f(radius));
};