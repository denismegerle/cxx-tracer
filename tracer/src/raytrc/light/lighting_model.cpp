#include "lighting_model.h"

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;

Vec3f raytrc::evaluate_phong(Vec3f lightDirection, Vec3f diffuseLight,
                     Vec3f specularLight, Intersection *intersection) {
  float distance = lightDirection.norm();
  Vec3f lightDirectionNormalized = lightDirection.normalize();

  /* calculating diffuse part */
  float diffuseReflectionComponent =
      intersection->normal * lightDirectionNormalized;

  Vec3f diffuse = (diffuseReflectionComponent > 0)
                      ? intersection->material.kd.mult(diffuseLight) *
                            diffuseReflectionComponent
                      : Vec3f(0.0f);

  /* calculate specular part */
  Vec3f reflectionDirection =
      2.0f * intersection->normal * diffuseReflectionComponent -
      lightDirectionNormalized;
  float specularReflectionComponent =
      reflectionDirection * intersection->negRayVector;

  Vec3f specular =
      (diffuseReflectionComponent > 0 && specularReflectionComponent > 0)
          ? intersection->material.ks.mult(specularLight) *
                powf(specularReflectionComponent, intersection->material.n)
          : Vec3f(0.0f);

  float distanceFactor = 1.0f / (distance * distance);

  return distanceFactor * (diffuse + specular);
}
