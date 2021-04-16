
#include <cassert>

#include "raytrc/geometry/cameras/pinhole_camera.h"
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

  this->paneTopLeft =
      (1.0f / 2.0f) * Vec2f(-this->imagePaneWidth, this->imagePaneHeight);
  this->paneSize = Vec2f(this->imagePaneWidth, this->imagePaneHeight);
}

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

Ray PinholeCamera::generateRay(int x, int y, int s) {
  Vec2f uv = this->getUV(x, y);

  Vec3f imagePanePoint = uv[0] * this->imagePaneX + uv[1] * this->imagePaneY -
                         this->distanceToImagePane * this->imagePaneNormal;

  return Ray(this->position, imagePanePoint);
}