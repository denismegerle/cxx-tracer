#pragma once

#include "maths/maths.h"
#include "pinhole_camera.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

class SupersamplingPinholeCamera : public PinholeCamera {
 public:
  int nSupersamples;
  Vec2f *samplingMatrix;

  SupersamplingPinholeCamera(Vec3f position, Vec3f target, Vec3f up,
                             int pixelWidth, int pixelHeight,
                             float distanceToImagePane, float fov,
                             int nSupersamples, Vec2f *samplingMatrix)
      : PinholeCamera(position, target, up, pixelWidth, pixelHeight,
                      distanceToImagePane, fov),
        nSupersamples(nSupersamples),
        samplingMatrix(samplingMatrix){};

  Ray generateRay(int x, int y, int s) override;
};

}  // namespace raytrc
