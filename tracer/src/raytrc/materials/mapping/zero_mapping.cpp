/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "zero_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"


using namespace raytrc;
using namespace std;

Vec2f ZeroMapping::get_uv(Intersection *intersection) const {
  return Vec2f(0.0f);
}