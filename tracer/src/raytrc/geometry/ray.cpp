/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "ray.h"

#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/material.h"

using namespace raytrc;
using namespace gem;

constexpr auto EPS_RAYS = 10e-6f;

/*!
 * Simple calculation
 */
Vec3f Ray::equate() { return this->origin + this->t * this->direction; }

/*!
 * Reflection without fresnel, good explanation see
 * @link{https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf}
 */
Ray Ray::reflect(Intersection *intersection) {
  Vec3f position = intersection->position + EPS_RAYS * intersection->normal;
  Vec3f direction =
      2.0f * (this->direction * intersection->normal) * intersection->normal -
      this->direction;
  return Ray(position, -1.0f * direction);
}

/*!
 * Refraction, good explanation see
 * @link{https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf}
 */
Ray Ray::refract(Intersection *intersection, float eta_1, float eta_2) {
  float theta_i_ = acos(this->direction.normalize().dot(intersection->normal));
  float theta_i = (theta_i_ > M_PI / 2.0f) ? M_PI - theta_i_ : theta_i_;

  Vec3f normal =
      (theta_i_ > M_PI / 2.0f) ? intersection->normal : -intersection->normal;

  Vec3f position = intersection->position - EPS_RAYS * normal;
  Vec3f direction = (eta_1 / eta_2) * this->direction.normalize() +
                    ((eta_1 / eta_2) * cos(theta_i) -
                     sqrt(1.0f - pow(eta_1 / eta_2, 2.0f) *
                                     (1.0f - pow(cos(theta_i), 2.0f)))) *
                        normal;
  return Ray(position, direction.normalize());
}