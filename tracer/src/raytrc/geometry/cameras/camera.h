#pragma once

#include "maths/maths.h"

using namespace gem;

namespace raytrc {

class Camera {
 public:
  Vec3f position, target, up;

  Camera(){};
  Camera(Vec3f position, Vec3f target, Vec3f up)
      : position(position), target(target), up(up.normalize()){};
};

}
