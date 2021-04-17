/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "latlng_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;

/*!
 * Basic equirectangular latlng projection
 */
Vec2f LatLngMapping::get_uv(Intersection *intersection) const {
  float azimuth = std::atan2(intersection->normal[1], intersection->normal[0]);
  float polar = std::acos(intersection->normal[2]);

  float u = 0.5f + azimuth / (2.0f * M_PI);
  float v = polar / M_PI;

  return scale.mult(Vec2f(u, v));
}
