#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/ray.h"
#include "ss_pinhole_camera.h"

using namespace gem;

namespace raytrc {

class SupersamplingLenseCamera : public SupersamplingPinholeCamera {
 public:
  float focusLength, aperture;

  SupersamplingLenseCamera(Vec3f position, Vec3f target, Vec3f up,
                           int pixelWidth, int pixelHeight,
                           float distanceToImagePane, float fov,
                           int nSupersamples, Vec2f *samplingMatrix,
                           float focusLength, float aperture)
      : SupersamplingPinholeCamera(position, target, up, pixelWidth,
                                   pixelHeight, distanceToImagePane, fov,
                                   nSupersamples, samplingMatrix),
        focusLength(focusLength),
        aperture(aperture){};

  Ray generateRay(int x, int y, int s) override;
};

}  // namespace raytrc
