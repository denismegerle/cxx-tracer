/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "light_source.h"
#include "maths/maths.h"

using namespace gem;

namespace raytrc {

class PointLight : public LightSource {
 public:
  Vec3f position;                    // pos
  Vec3f ambient, diffuse, specular;  // light components

  PointLight(Vec3f position, Vec3f intensity)
      : position(position),
        ambient(intensity),
        diffuse(intensity),
        specular(intensity){};

  PointLight(Vec3f position, Vec3f ambient, Vec3f diffuse, Vec3f specular)
      : position(position),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular){};

  Vec3f computeDirectLight(World *world, Intersection *intersection);
};

}  // namespace raytrc
