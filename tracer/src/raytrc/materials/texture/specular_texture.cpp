#include <cmath>

#include "CImg.h"
#include "specular_texture.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

void SpecularTexture::applyOn(Intersection *intersection, Vec2f uv,
                           Vec2f dudv) const {
  Vec2f st = this->get_st(uv);
  Vec3f ks = this->modifier.mult(this->evaluate(st));

  intersection->material.ks = ks;
};