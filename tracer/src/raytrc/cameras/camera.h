/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Basic camera class, modelling a camera in world space. Can retrieve
 * image pixel ray (as a sample) given its coordinates and sample id.
 */
class Camera {
 public:
  Vec3f position; /*!< position of the camera */
  Vec3f target;   /*!< position camera is pointed at */
  Vec3f up;       /*!< up position of the camera */

  /*!
   * @brief Standard initializing the camera parameters, vectors are normalized
   * on creation
   * @param position position of camera in world space
   * @param target target of camera in world space
   * @param up up vector in world space
   */
  Camera(Vec3f position, Vec3f target, Vec3f up)
      : position(position), target(target), up(up.normalize()){};

  /*!
   * @brief Ray generation given the position of the camera, its target and the
   * pixel position x/y.
   * @param x pixel x
   * @param y pixel y
   * @param s sample id s
   * @return ray that the camera would produce, through pixel position x/y
   * (depending on the camera model might be stochastic, with sample id s
   * constant)
   */
  virtual Ray generateRay(int x, int y, int s) = 0;
};

}  // namespace raytrc
