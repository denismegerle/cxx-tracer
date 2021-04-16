/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "pinhole_camera.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Camera that super samples, can have different sampling pattern (using
 * sample matrices).
 */
class SupersamplingPinholeCamera : public PinholeCamera {
 public:
  int nSupersamples;     /*!< amount of supersamples per pixel */
  Vec2f *samplingMatrix; /*!< sampling matrix, 3d (w x h x s) */

  /*!
   * @brief Very similar to the pinhole camera, but instead of fixed centeres
   * pertuberates them based on the sample matrix.
   * @param nSupersamples amount of samples per pixel
   * @param samplingMatrix sample matrix, 3d (w x h x s)
   */
  SupersamplingPinholeCamera(Vec3f position, Vec3f target, Vec3f up,
                             int pixelWidth, int pixelHeight,
                             float distanceToImagePane, float fov,
                             int nSupersamples, Vec2f *samplingMatrix)
      : PinholeCamera(position, target, up, pixelWidth, pixelHeight,
                      distanceToImagePane, fov),
        nSupersamples(nSupersamples),
        samplingMatrix(samplingMatrix){};

  /*!
   * @brief Similar ray generation to the pinhole camera, just pertuberating the
   * points on the image pane.
   */
  Ray generateRay(int x, int y, int s) override;
};

}  // namespace raytrc
