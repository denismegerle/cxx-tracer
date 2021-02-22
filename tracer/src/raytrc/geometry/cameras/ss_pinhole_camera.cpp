
#include <cassert>

#include "maths/maths.h"
#include "raytrc/geometry/cameras/ss_pinhole_camera.h"

using namespace raytrc;
using namespace gem;

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

Ray SupersamplingPinholeCamera::generateRay(int x, int y) {
  Vec2f pixelSizeOnPane(this->imagePaneHeight / this->pixelHeight,
                        this->imagePaneWidth / this->pixelWidth);

  Vec2f randomVector((float)random_double() - 0.5f,
                     (float)random_double() - 0.5f);
  Vec2f uv = this->getUV(x, y) + this->samplingVariance * randomVector.mult(pixelSizeOnPane);

  Vec3f imagePanePoint = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                         this->distanceToImagePane * this->imagePaneNormal;

  return Ray(this->position, imagePanePoint);

}