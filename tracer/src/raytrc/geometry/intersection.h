#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/objects/material.h"

using namespace gem;

namespace raytrc {

class Intersection {
 public:
  Vec3f position, normal, negRayVector;  // pos, normale, vector to origin of ray
  Material *material;

  Intersection(){};
  Intersection(Vec3f position, Vec3f normal, Vec3f negRayVector,
               Material *material)
      : position(position),
        normal(normal),
        negRayVector(negRayVector),
        material(material){};
};

}  // namespace raytrc