/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "light_source.h"
#include "maths/maths.h"

using namespace gem;

namespace raytrc {

class AmbientLight : public LightSource {
 public:
  Vec3f position, intensity;  // pos + intensity I_L (rgb)

  AmbientLight(Vec3f position, Vec3f intensity)
      : position(position), intensity(intensity){};

  Vec3f computeDirectLight(World *world, Intersection *intersection);
};

}  // namespace raytrc
