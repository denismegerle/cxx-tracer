
#include "world.h"

#include <vector>

using namespace raytrc;
using namespace gem;

// closest intersection point (with closest object)
bool World::cast(Ray *ray, Intersection *intersection) { 
  std::vector<float> tValues;
  bool intersected = false;

  Ray rayCopy = Ray(*ray);
  Intersection tempIntersection;
  for (int i = 0; i < objects.size(); i++) {
    tValues.push_back(FLT_MAX);

    if (objects[i]->intersect(&rayCopy, &tempIntersection) && rayCopy.t > 0) {
      tValues[i] = rayCopy.t;
      intersected = true;
    }
  }

  if (!intersected) return false;

  int minTIndex =
      std::min_element(tValues.begin(), tValues.end()) - tValues.begin();

  objects[minTIndex]->intersect(ray, intersection);
  return true;
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

  return i.material->kt;
}