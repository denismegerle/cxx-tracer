#pragma once

#include "maths/maths.h"
#include "pinhole_camera.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

class SupersamplingLensePinholeCamera : public PinholeCamera {
 public:
  float samplingVariance;
  SupersamplingLensePinholeCamera(Vec3f position, Vec3f target, Vec3f up,
                             int pixelWidth, int pixelHeight,
                             float distanceToImagePane, float fov = M_PI / 2.0f,
                             float samplingVariance = 1.0f)
      : PinholeCamera(position, target, up, pixelWidth, pixelHeight,
                      distanceToImagePane, fov),
        samplingVariance(samplingVariance){};
  ;

  Ray generateRay(int x, int y);
};

}  // namespace raytrc
