#include <cmath>

#include "CImg.h"
#include "environment_texture.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

void EnvironmentTexture::applyOn(Intersection *intersection, Vec2f uv,
                             Vec2f dudv) const {
  Vec2f st = this->get_st(uv);
  Vec3f kd = this->modifier.mult(this->evaluate(st));

  intersection->material.kd = kd;
};