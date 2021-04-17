/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "planar_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;

/*!
 * According to formula
 * (u v) = (s t) * (S T)
 */
Vec2f PlanarMapping::get_uv(Intersection *intersection) const {
  float u = (intersection->position - this->position) * s_axis;
  float v = (intersection->position - this->position) * t_axis;

  return scale.mult(Vec2f(u, v));
}
