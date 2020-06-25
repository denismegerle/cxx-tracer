
#include "point_light.h"
#include "raytrc/world.h"

using namespace raytrc;
using namespace gem;

constexpr auto EPS_SHADOW = 10e-7;

/*
according to PHONG lighting model,
*/
Vec3f PointLight::computeDirectLight(World *world, Intersection *intersection) {
  /* calculating whether we need to cast shadow */
  Vec3f lightDirection = (this->position - intersection->position).normalize();
  float distance = (this->position - intersection->position).norm();

  Vec3f transmissionFactor(1.0f);

  // finding intersecting objects of the ray from intersection to the light
  Intersection i;
  Ray r(intersection->position + intersection->normal.mult(Vec3f(EPS_SHADOW)), this->position - intersection->position);
  if (world->cast(&r, &i) &&
      r.t < 1.0f) {       // obj between this and light blocks the light
    transmissionFactor = i.material->kt;
  }
  // if (transmissionFactor.norm() <= 0.001f) return Vec3f(0.0f);   // no transmission = no light from this source

  /* calculate ambient part */
  Vec3f ambient = intersection->material->ka.mult(this->intensity);

  /* calculating diffuse part */
  float diffuseReflectionComponent = intersection->normal * lightDirection;

  Vec3f diffuse = (diffuseReflectionComponent > 0)
                      ? intersection->material->kd.mult(this->intensity) *
                            diffuseReflectionComponent
                      : Vec3f(0.0f);

  /* calculate specular part */
  Vec3f reflectionDirection =
      2.0f * intersection->normal * diffuseReflectionComponent - lightDirection;
  float specularReflectionComponent =
      reflectionDirection * intersection->negRayVector;

  Vec3f specular =
      (diffuseReflectionComponent > 0 && specularReflectionComponent > 0)
          ? intersection->material->ks.mult(this->intensity) *
                powf(specularReflectionComponent, intersection->material->n)
          : Vec3f(0.0f);

  float distanceFactor = 1.0f / (distance * distance);

  return transmissionFactor.mult(ambient +
         distanceFactor * (diffuse + specular));
}