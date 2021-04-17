/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "spherical_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;

/*!
 * Spherical mapping according to OpenGL, see
 * @link{https://www.opengl.org/archives/resources/code/samples/advanced/advanced97/notes/node94.html#SECTION000113210000000000000},
 * with coordinate system up = (0, 0, 1)
 */
Vec2f SphericalMapping::get_uv(Intersection *intersection) const {
  Vec3f R = intersection->normal;

  // coordinate system's up is (0, 0, 1), assuming a const viewer v = (-1, 0, 0)
  float m = 2.0f * std::sqrtf(std::powf(R[1], 2.0f) + std::powf(-R[2], 2.0f) +
                              std::powf(1.0f + R[0], 2.0f));

  float u = R[1] / m + 0.5f;
  float v = -R[2] / m + 0.5f;

  return Vec2f(u, v);
}
