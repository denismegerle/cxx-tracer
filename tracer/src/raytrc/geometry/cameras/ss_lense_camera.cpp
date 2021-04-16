
#include "raytrc/geometry/cameras/ss_lense_camera.h"

#include <cassert>

#include "maths/maths.h"

using namespace raytrc;
using namespace gem;

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

Ray SupersamplingLenseCamera::generateRay(int x, int y, int s) {
  Vec2f pixelSizeOnPane(this->imagePaneHeight / this->pixelHeight,
                        this->imagePaneWidth / this->pixelWidth);

  Vec2f xy = this->samplingMatrix[x * this->nSupersamples * this->pixelHeight +
                                  y * this->nSupersamples + s];

  Vec2f uv = this->getUV(xy[0], xy[1]);

  Vec3f imagePaneVector = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                          this->distanceToImagePane * this->imagePaneNormal;

  Vec3f focusPoint =
      this->position + (imagePaneVector.norm() /
                        (this->distanceToImagePane /
                         (this->distanceToImagePane + this->focusLength))) *
                           imagePaneVector;

  float rdX = (float)random_double() - 0.5f;
  float rdY = (float)random_double() - 0.5f;

  Vec3f newPosition = this->position + imagePaneVector +
                      this->imagePaneX * rdX * this->aperture +
                      this->imagePaneY * rdY * this->aperture;

  return Ray(newPosition, focusPoint - newPosition);
}