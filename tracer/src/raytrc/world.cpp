
#include "world.h"

#include <vector>

using namespace raytrc;
using namespace gem;

bool World::cast(Ray *ray, Intersection *intersection) { 
  std::vector<float> tValues;
  bool intersected = false;

  Ray *rayCopy = new Ray(*ray);
  Intersection tempIntersection;
  for (int i = 0; i < objects.size(); i++) {
    tValues.push_back(FLT_MAX);

    if (objects[i]->intersect(rayCopy, &tempIntersection) && rayCopy->t > 0) {
      tValues[i] = rayCopy->t;
      intersected = true;
    }
  }

  if (!intersected) return false;

  int minTIndex =
      std::min_element(tValues.begin(), tValues.end()) - tValues.begin();

  objects[minTIndex]->intersect(ray, intersection);
  return true;
}