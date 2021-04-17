/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "cube_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;

void convert_xyz_to_cube_uv(float x, float y, float z, uint8_t *index, float *u,
                            float *v);

/*!
 * 3x4 region combined in one image,
 * [ 0 t 0 0 ]
 * [ l o r u ]  (o in front, u behind)
 * [ 0 b 0 0 ]
 * --> selects the region and then calculates, relative to top left of image,
 * what the uv coordinates would be. Thus uv is always in [0,1].
 */
Vec2f CubeMapping::get_uv(Intersection *intersection) const {
  static const uint8_t FACES_X = 4;
  static const uint8_t FACES_Y = 3;

  uint8_t index;
  float u, v;

  convert_xyz_to_cube_uv(intersection->normal[1], -intersection->normal[2],
                         intersection->normal[0], &index, &u, &v);
  u /= FACES_X;
  v /= FACES_Y;

  u = (index % FACES_X) * (1.0f / FACES_X) + u;
  v = (index / FACES_X) * (1.0f / FACES_Y) + v;

  return Vec2f(u, v);
}

void convert_xyz_to_cube_uv(float x, float y, float z, uint8_t *index, float *u,
                            float *v) {
  float absX = std::fabs(x);
  float absY = std::fabs(y);
  float absZ = std::fabs(z);

  int isXPositive = x > 0 ? 1 : 0;
  int isYPositive = y > 0 ? 1 : 0;
  int isZPositive = z > 0 ? 1 : 0;

  float maxAxis, uc, vc;

  // POSITIVE X
  if (isXPositive && absX >= absY && absX >= absZ) {
    // u (0 to 1) goes from +z to -z
    // v (0 to 1) goes from -y to +y
    maxAxis = absX;
    uc = -z;
    vc = y;
    *index = 6;
  }
  // NEGATIVE X
  if (!isXPositive && absX >= absY && absX >= absZ) {
    // u (0 to 1) goes from -z to +z
    // v (0 to 1) goes from -y to +y
    maxAxis = absX;
    uc = z;
    vc = y;
    *index = 4;
  }
  // POSITIVE Y
  if (isYPositive && absY >= absX && absY >= absZ) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from +z to -z
    maxAxis = absY;
    uc = x;
    vc = -z;
    *index = 9;
  }
  // NEGATIVE Y
  if (!isYPositive && absY >= absX && absY >= absZ) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from -z to +z
    maxAxis = absY;
    uc = x;
    vc = z;
    *index = 1;
  }
  // POSITIVE Z
  if (isZPositive && absZ >= absX && absZ >= absY) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from -y to +y
    maxAxis = absZ;
    uc = x;
    vc = y;
    *index = 5;
  }
  // NEGATIVE Z
  if (!isZPositive && absZ >= absX && absZ >= absY) {
    // u (0 to 1) goes from +x to -x
    // v (0 to 1) goes from -y to +y
    maxAxis = absZ;
    uc = -x;
    vc = y;
    *index = 7;
  }

  // Convert range from -1 to 1 to 0 to 1
  *u = 0.5f * (uc / maxAxis + 1.0f);
  *v = 0.5f * (vc / maxAxis + 1.0f);
}
