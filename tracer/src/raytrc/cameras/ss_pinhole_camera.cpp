/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "ss_pinhole_camera.h"

#include "maths/maths.h"

using namespace raytrc;
using namespace gem;

/*!
 * Ray generation chooses the uv coordinates according to the sample matrix xy
 * coordinates. These can be shifted as necessary from the center of the pixel.
 */
Ray SupersamplingPinholeCamera::generateRay(int x, int y, int s) {
  Vec2f pixelSizeOnPane(this->imagePaneHeight / this->pixelHeight,
                        this->imagePaneWidth / this->pixelWidth);

  Vec2f xy = this->samplingMatrix[x * this->nSupersamples * this->pixelHeight +
                                  y * this->nSupersamples + s];
  Vec2f uv = this->getUV(xy[0], xy[1]);

  Vec3f imagePanePoint = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                         this->distanceToImagePane * this->imagePaneNormal;

  return Ray(this->position, imagePanePoint);
}