/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "sphere_light.h"

#include "maths/maths.h"
#include "raytrc/const.h"
#include "raytrc/light/lighting_model.h"
#include "raytrc/sampling/random.h"
#include "raytrc/world.h"

using namespace raytrc;
using namespace gem;

/*!
 * More complex and stochastic light calcuation: Light is modeled as a spherical
 * source, thus shadow rays can partly reach and partly not reach the light,
 * generating soft shadows.
 */
Vec3f SphereLight::computeDirectLight(World *world,
                                      Intersection *intersection) {
  /* calculating whether we need to cast shadow */
  Vec3f lightDirectionNormalized =
      (this->position - intersection->position).normalize();
  Vec3f perpendicularToLight = lightDirectionNormalized.cross(
      Vec3f(0.0f, 0.0f, 1.0f));  // cross world up vector
  if (perpendicularToLight.norm() == 0) {
    perpendicularToLight = Vec3f(0.0f, 1.0f, 0.0f);
  }

  Vec3f lightSphereEdge =
      (this->position + this->radius * perpendicularToLight);

  float z = random_double() * this->radius;
  float phi = random_double() * 2.0f * M_PI;

  // using the rodriguez rotation formula
  Mat3f W(0.0f, -lightDirectionNormalized[2], lightDirectionNormalized[1],
          lightDirectionNormalized[2], 0.0f, -lightDirectionNormalized[0],
          -lightDirectionNormalized[1], lightDirectionNormalized[0], 0.0f);
  Mat3f R = Mat3f(1.0f, 1.0f, 1.0f) + sin(phi) * W +
            (2.0f * pow(sin(phi / 2.0f), 2.0f)) * W * W;

  Vec3f rdPointOnDisc = this->position + R * (z * perpendicularToLight);

  Vec3f lightDirection = rdPointOnDisc - intersection->position;

  Vec3f transmissionFactor(1.0f);

  // finding intersecting objects of the ray from intersection to the light
  Intersection i;
  Ray r(intersection->position + EPS_SHADOW * intersection->normal,
        lightDirection);
  if (world->cast(&r, &i) &&
      r.t < 1.0f) {  // obj between this and light blocks the light
    // transmissionFactor = world->deriveTransmissionFactor(&r);
    return Vec3f(0.0f);
  }

  Vec3f phongLighting = evaluate_phong(lightDirection, this->diffuse,
                                       this->specular, intersection);
  return transmissionFactor.mult(phongLighting);
}