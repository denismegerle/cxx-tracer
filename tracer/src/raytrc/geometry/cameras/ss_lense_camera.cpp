
#include "raytrc/geometry/cameras/ss_lense_camera.h"

#include <cassert>

#include "maths/maths.h"

using namespace raytrc;
using namespace gem;

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

Ray SupersamplingLensePinholeCamera::generateRay(int x, int y) {
  Vec2f pixelSizeOnPane(this->imagePaneHeight / this->pixelHeight,
                        this->imagePaneWidth / this->pixelWidth);

  Vec2f randomVector((float)random_double() - 0.5f,
                     (float)random_double() - 0.5f);
  Vec2f uv = this->getUV(x, y) +
             this->samplingVariance * randomVector.mult(pixelSizeOnPane);

  Vec3f imagePaneVector = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                          this->distanceToImagePane * this->imagePaneNormal;

  float focusLength = 5.25f;
  float aperture = 0.1f;

  Vec3f focusPoint =
      this->position +
      (imagePaneVector.norm() / (this->distanceToImagePane /
                                 (this->distanceToImagePane + focusLength))) *
          imagePaneVector;

  float rdX = (float)random_double() - 1.0f;
  float rdY = (float)random_double() - 1.0f;

  Vec3f newPosition = this->position + imagePaneVector +
                      this->imagePaneX * rdX * aperture +
                      this->imagePaneY * rdY * aperture;

  return Ray(newPosition, focusPoint - newPosition);
}