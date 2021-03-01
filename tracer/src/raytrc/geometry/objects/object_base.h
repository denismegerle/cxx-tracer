#pragma once

#include <tuple>
#include <vector>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/material.h"
#include "raytrc/geometry/ray.h"
#include "raytrc/texture/mapping/texture_mapping.h"
#include "raytrc/texture/texture.h"

using namespace gem;

namespace raytrc {

class ObjectBase {
 public:
  Vec3f position;
  std::vector<std::tuple<std::shared_ptr<TextureMapping>, const Texture *>> textures;

  ObjectBase(){};
  ObjectBase(Vec3f position) : position(position){};

  /* calculates closest intersection in positive direction */
  virtual bool intersect(Ray *ray, Intersection *intersection) = 0;
};

}  // namespace raytrc