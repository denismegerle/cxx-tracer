
#include "sphere_light.h"

#include "maths/maths.h"
#include "raytrc/world.h"

using namespace raytrc;
using namespace gem;

constexpr auto EPS_SHADOW = 10e-6f;

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

/*
according to PHONG lighting model,
*/
Vec3f SphereLight::computeDirectLight(World *world,
                                      Intersection *intersection) {
  /* calculating whether we need to cast shadow */
  Vec3f lightDirectionUnnormalized = this->position - intersection->position;
  Vec3f lightDirection = (this->position - intersection->position).normalize();
  Vec3f perpendicularToLight =
      lightDirection.cross(Vec3f(0.0f, 0.0f, 1.0f));  // cross world up vector
  if (perpendicularToLight.norm() == 0) {
    perpendicularToLight = Vec3f(0.0f, 1.0f, 0.0f);
  }

  Vec3f lightSphereEdge =
      (this->position + this->radius * perpendicularToLight);

  float z = random_double() * this->radius;
  float phi = random_double() * 2.0f * M_PI;

  // using the rodriguez rotation formula
  Mat3f W(0.0f, -lightDirection[2], lightDirection[1], lightDirection[2], 0.0f,
          -lightDirection[0], -lightDirection[1], lightDirection[0], 0.0f);
  Mat3f R = Mat3f(1.0f, 1.0f, 1.0f) + sin(phi) * W +
            (2.0f * pow(sin(phi / 2.0f), 2.0f)) * W * W;

  Vec3f rdPointOnDisc =
      this->position + R * (z * this->radius * perpendicularToLight);

  lightDirection = (rdPointOnDisc - intersection->position).normalize();
  lightDirectionUnnormalized = rdPointOnDisc - intersection->position;

  float distance = (this->position - intersection->position).norm();

  Vec3f transmissionFactor(1.0f);

  // finding intersecting objects of the ray from intersection to the light
  Intersection i;
  Ray r(intersection->position + EPS_SHADOW * intersection->normal,
        lightDirectionUnnormalized);
  if (world->cast(&r, &i) &&
      r.t < 1.0f) {  // obj between this and light blocks the light
    transmissionFactor = Vec3f(0.0f);
  }

  /* calculate ambient part */
  Vec3f ambient = intersection->material->ka.mult(this->ambient);

  /* calculating diffuse part */
  float diffuseReflectionComponent = intersection->normal * lightDirection;

  Vec3f diffuse = (diffuseReflectionComponent > 0)
                      ? intersection->material->kd.mult(this->diffuse) *
                            diffuseReflectionComponent
                      : Vec3f(0.0f);

  /* calculate specular part */
  Vec3f reflectionDirection =
      2.0f * intersection->normal * diffuseReflectionComponent - lightDirection;
  float specularReflectionComponent =
      reflectionDirection * intersection->negRayVector;

  Vec3f specular =
      (diffuseReflectionComponent > 0 && specularReflectionComponent > 0)
          ? intersection->material->ks.mult(this->specular) *
                powf(specularReflectionComponent, intersection->material->n)
          : Vec3f(0.0f);

  float distanceFactor = 1.0f / (distance * distance);

  return ambient +
         transmissionFactor.mult(distanceFactor * (diffuse + specular));
}