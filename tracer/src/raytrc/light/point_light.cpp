/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "point_light.h"

#include "raytrc/world.h"
#include "raytrc/light/lighting_model.h"

using namespace raytrc;
using namespace gem;

constexpr auto EPS_SHADOW = 10e-6f;

/*
according to PHONG lighting model,
*/
Vec3f PointLight::computeDirectLight(World *world, Intersection *intersection) {
  /* calculating whether we need to cast shadow */
  Vec3f lightDirection = this->position - intersection->position;

  Vec3f transmissionFactor(1.0f);

  // finding intersecting objects of the ray from intersection to the light
  Intersection i;
  Ray r(intersection->position + EPS_SHADOW * intersection->normal,
        lightDirection);
  if (world->cast(&r, &i) &&
      r.t < 1.0f) {  // obj between this and light blocks the light
    transmissionFactor =
        Vec3f(0.0f);  // could be kt or specific transmission factor of material
                      // (or kt * depth, exp func of thickness)
  }

  Vec3f phongLighting =
      evaluate_phong(lightDirection, this->diffuse, this->specular, intersection);
  return transmissionFactor.mult(phongLighting);
}