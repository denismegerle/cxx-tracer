/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/cameras/ss_pinhole_camera.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Supersampling lense camera models a camera that supersamples for
 * antialiasing but imitates an imperfect camera model with aperture and a
 * lense. A point on the lense is randomly chosen and a ray generated that
 * reaches the same focal point.
 */
class SupersamplingLenseCamera : public SupersamplingPinholeCamera {
 public:
  float focusLength; /*!< focal length (lense to focal point, defines focal
                        plane) */
  float aperture;    /*!< aperture of camera, defines strength of focus */

  /*!
   * @brief Generates a supersampling lense camera
   * @param focusLength focal length (lense - focal plane distance)
   * @param aperture aperture of camera
   */
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

  /*!
   * @brief Similar to supersampling pinhole camera, but stochastic by randomly
   * sampling a origin position on the lense that would reach the same focal
   * point than the original ray.
   */
  Ray generateRay(int x, int y, int s) override;
};

}  // namespace raytrc
