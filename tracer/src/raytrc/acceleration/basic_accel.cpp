#include "basic_accel.h"

#include <memory>
#include <vector>

#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"

using namespace raytrc;

bool BasicAccel::cast(Ray *ray, Intersection *intersection){
  std::vector<float> tValues;
  bool intersected = false;

  Ray rayCopy = Ray(*ray);
  Intersection tempIntersection;
  for (int i = 0; i < this->objects.size(); i++) {
    tValues.push_back(FLT_MAX);

    if (this->objects[i]->intersect(&rayCopy, &tempIntersection) && rayCopy.t > 0) {
      tValues[i] = rayCopy.t;
      intersected = true;
    }
  }

  if (!intersected) return false;

  int minTIndex =
      std::min_element(tValues.begin(), tValues.end()) - tValues.begin();

  this->objects[minTIndex]->intersect(ray, intersection);
  return true;
};
