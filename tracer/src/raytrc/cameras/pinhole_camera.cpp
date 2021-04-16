/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "pinhole_camera.h"

#include <cassert>

#include "maths/maths.h"

using namespace raytrc;
using namespace gem;

/*!
 * Mostly calculates image pane parameters, such as pixel size and image pane
 * position, as well as u/v/w vectors of the camera according to a basic pinhole
 * model such as described in
 * @link{https://en.wikipedia.org/wiki/Pinhole_camera_model}
 */
PinholeCamera::PinholeCamera(Vec3f position, Vec3f target, Vec3f up,
                             int pixelWidth, int pixelHeight,
                             float distanceToImagePane, float fov)
    : Camera(position, target, up),
      pixelWidth(pixelWidth),
      pixelHeight(pixelHeight),
      distanceToImagePane(distanceToImagePane),
      fov(fov) {
  this->aspect = static_cast<float>(pixelWidth) / pixelHeight;

  this->imagePaneNormal = (position - target).normalize();
  this->imagePaneX = this->imagePaneNormal.cross(up).normalize();
  this->imagePaneY = this->imagePaneX.cross(this->imagePaneNormal).normalize();
  this->imagePaneHeight = 2 * tan(fov / 2.0f) * this->distanceToImagePane;
  this->imagePaneWidth = this->aspect * this->imagePaneHeight;

  this->paneTopLeft =
      (1.0f / 2.0f) * Vec2f(-this->imagePaneWidth, this->imagePaneHeight);
  this->paneSize = Vec2f(this->imagePaneWidth, this->imagePaneHeight);
}

/*!
 * Calculates the u/v coordinates of a pixel given in x/y coordinates. The u/v
 * coordinates are the coordinates on the image pane. Shifting pixels by 0.5 to
 * accord for the center point of the pixel.
 */
Vec2f PinholeCamera::getUV(float x, float y) {
  /*
    Standard no-lense pinhole model:
    Calculate the top left of the pane, the pane total dimensions
    and with the given x, y / xtotal, ytotal the image to pane ratio
  */
  Vec2f pixelScale((x + 0.5f) / this->pixelWidth,
                   -(y + 0.5f) / this->pixelHeight);

  return paneTopLeft + paneSize.mult(pixelScale);
}

/*!
 * Basic pinhole ray generation, given the formula
 * r = p + dt, where p camera position and
 * d = normalize(u*U + v*V - f*W) (f focal length).
 */
Ray PinholeCamera::generateRay(int x, int y, int s) {
  Vec2f uv = this->getUV(x, y);

  Vec3f imagePanePoint = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                         this->distanceToImagePane * this->imagePaneNormal;

  return Ray(this->position, imagePanePoint);
}