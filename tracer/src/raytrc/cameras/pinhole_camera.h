/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "camera.h"
#include "maths/maths.h"
#include "raytrc/geometry/ray.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Pinhole Camera model, see Wikipedia.
 */
class PinholeCamera : public Camera {
 public:
  Vec3f imagePaneNormal; /*!< normal of the image pane in world space */
  Vec3f imagePaneX;      /*!< U vector */
  Vec3f imagePaneY;      /*!< V vector */

  float imagePaneWidth;  /*!< width of image pane in world space */
  float imagePaneHeight; /*!< height of image pane in world space */

  Vec2f paneTopLeft; /*!< top left image pane point */
  Vec2f paneSize;    /*!< total pane size in world coordinates */

  float distanceToImagePane; /*!< distance to image pane in world coordinates*/
  float fov;                 /*!< field of vision in radians */
  float aspect;              /*!< aspect ratio, calculated automatically */

  int pixelWidth;
  int pixelHeight;

  /*!
   * @brief Pinhole Camera model initialization, all common calculations.
   * @param position position of camera
   * @param target camera is pointed at target
   * @param up up vector in world space, will be normalized
   * @param pixelWidth pixel width
   * @param pixelHeight pixel height
   * @param distanceToImagePane distance to image pane
   * @param fov field of view, i.e. angle center to one side (45deg per default)
   */
  PinholeCamera(Vec3f position, Vec3f target, Vec3f up, int pixelWidth,
                int pixelHeight, float distanceToImagePane,
                float fov = M_PI / 2.0f);

  /*!
   * @brief Generating a ray through pixel x/y, with sample id s.
   * @param x pixel x
   * @param y pixel y
   * @param s sample id s
   * @return ray from origin (position of camera) to image pane point
   */
  Ray generateRay(int x, int y, int s) override;

 protected:
  /*!
   * @brief Getting the coordinates in world space on the image pane, given pixel coordinates.
   * @param x pixel x
   * @param y pixel y
   * @return uv coordinates in world space
   */
  Vec2f getUV(float x, float y);
};

}  // namespace raytrc
