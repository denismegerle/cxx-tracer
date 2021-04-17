/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

namespace raytrc {

class TextureMapping {
 public:
  virtual Vec2f get_uv(Intersection *intersection) const = 0;
};

}
