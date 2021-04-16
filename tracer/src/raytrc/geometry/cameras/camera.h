#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

class Camera {
 public:
  Vec3f position, target, up;

  Camera(Vec3f position, Vec3f target, Vec3f up)
      : position(position), target(target), up(up.normalize()){};

  virtual Ray generateRay(int x, int y, int s) = 0;
};

}
