/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "ambient_light.h"

#include "raytrc/world.h"

using namespace raytrc;
using namespace gem;

/*!
 * Computes only an ambient term, i.e. only the light intensity and material
 * ambient property define the RGB values.
 */
Vec3f AmbientLight::computeDirectLight(World *world,
                                       Intersection *intersection) {
  return intersection->material.ka.mult(this->intensity);
}