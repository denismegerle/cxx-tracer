/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "light_source.h"
#include "maths/maths.h"

using namespace gem;

namespace raytrc {

/* actually not really spherical, but more a disc for simplification */
class SphereLight : public LightSource {
 public:
  Vec3f position;                    // pos
  float radius;                      // radius of the light
  Vec3f ambient, diffuse, specular;  // light components

  SphereLight(Vec3f position, float radius, Vec3f intensity)
      : position(position),
        radius(radius),
        ambient(intensity),
        diffuse(intensity),
        specular(intensity){};

  SphereLight(Vec3f position, float radius, Vec3f ambient, Vec3f diffuse,
              Vec3f specular)
      : position(position),
        radius(radius),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular){};

  Vec3f computeDirectLight(World *world, Intersection *intersection);
};

}  // namespace raytrc
