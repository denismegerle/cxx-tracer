
#include "point_light.h"

using namespace raytrc;
using namespace gem;

/*
according to PHONG lighting model,
*/
Vec3f PointLight::computeDirectLight(Intersection *intersection) {
  /* calculate ambient part */
  Vec3f ambient = intersection->material->ka.mult(this->intensity);

  /* calculating diffuse part */
  Vec3f lightDirection = (this->position - intersection->position).normalize();
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

  return ambient + diffuse + specular;
}