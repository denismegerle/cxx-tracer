/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "aabb.h"

#include <algorithm>

#include "maths/maths.h"

using namespace raytrc;
using namespace gem;

/*!
 * Combination via min max per dimension
 */
AABB AABB::combine(AABB other) {
  Vec3f newMin, newMax;

  for (int i = 0; i < 3; i++) {
    newMin[i] = this->min[i] < other.min[i] ? this->min[i] : other.min[i];
    newMax[i] = this->max[i] > other.max[i] ? this->max[i] : other.max[i];
  }

  return AABB(newMin, newMax);
};

/*!
 * Maximum dimension calculation
 */
uint8_t AABB::getMaxDimension() {
  Vec3f diff = this->max - this->min;

  int maxDimXY = diff[0] > diff[1] ? 0 : 1;
  int maxDim = diff[2] > diff[maxDimXY] ? 2 : maxDimXY;

  return maxDim;
};

/*!
 * The intersection test against an AABB is the fast intersection test from the
 * CGI lecture at KIT (Dachsbauer), somewhat similar to
 * @link{https://www.iquilezles.org/www/articles/intersectors/intersectors.htm}
 */
bool AABB::intersect(Ray *ray) {
  for (int i = 0; i < 3; i++) {
    if (ray->direction[i] == 0 &&
        (ray->origin[i] < this->min[i] || ray->origin[i] > this->max[i]))
      return false;
  }

  Vec3f t1 = (min - ray->origin).div(ray->direction);
  Vec3f t2 = (max - ray->origin).div(ray->direction);

  float tN = -FLT_MAX;
  float tF = FLT_MAX;

  for (int i = 0; i < 3; i++) {
    if (t1[i] > t2[i]) {
      float tmp = t1[i];
      t1[i] = t2[i];
      t2[i] = tmp;
    }

    tN = std::max(tN, t1[i]);
    tF = std::min(tF, t2[i]);
  }

  if (tF > tN && (tN > 0 || tF > 0)) return true;
  return false;
};