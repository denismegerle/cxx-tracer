
#include "world.h"

#include <vector>

#include "raytrc/acceleration/bvh.h"

using namespace raytrc;
using namespace gem;

// closest intersection point (with closest object)
bool World::cast(Ray *ray, Intersection *intersection) {
  return accelerationStructure->cast(ray, intersection);
}

/*
ray origin is expected to be at the object,
direction should be vector from object to target (e.g. light source)
*/
Vec3f World::deriveTransmissionFactor(Ray *ray) {
  // for now just calculating the closest object kt inefficiently, TODO improve
  Intersection i;
  Ray rayCopy = Ray(*ray);
  if (!this->cast(ray, &i) || rayCopy.t >= 1.0f) return Vec3f(0.0f);

  return i.material.kt;
}