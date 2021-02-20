
#include "raytrc/geometry/cameras/pinhole_camera.h"

#include <cassert>

#include "maths/maths.h"

using namespace raytrc;
using namespace gem;

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
}

Vec2f PinholeCamera::getUV(int x, int y) {
  assert(x >= 0 && x < this->pixelWidth);
  assert(y >= 0 && y < this->pixelHeight);

  /*
    Standard no-lense pinhole model:
    Calculate the top left of the pane, the pane total dimensions
    and with the given x, y / xtotal, ytotal the image to pane ratio
  */
  Vec2f paneTopLeft =
      (1.0f / 2.0f) * Vec2f(-this->imagePaneWidth, this->imagePaneHeight);
  Vec2f paneSize(this->imagePaneWidth, this->imagePaneHeight);
  Vec2f pixelScale((x + 0.5f) / this->pixelWidth,
                   -(y + 0.5f) / this->pixelHeight);

  return paneTopLeft + paneSize.mult(pixelScale);  // here mult is elementwise!
}

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

Ray PinholeCamera::generateRay(int x, int y) {
  Vec2f uv = this->getUV(x, y);

  Vec3f imagePanePoint = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                         this->distanceToImagePane * this->imagePaneNormal;

  return Ray(this->position, imagePanePoint);
}

Ray PinholeCamera::generateRay(int x, int y, float variance) {
  Vec2f pixelSizeOnPane(this->imagePaneHeight / this->pixelHeight,
                        this->imagePaneWidth / this->pixelWidth);

  Vec2f randomVector((float) random_double() - 0.5f, (float) random_double() - 0.5f);
  Vec2f uv = this->getUV(x, y) + variance * randomVector.mult(pixelSizeOnPane);

  Vec3f imagePanePoint = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                         this->distanceToImagePane * this->imagePaneNormal;

  return Ray(this->position, imagePanePoint);
}