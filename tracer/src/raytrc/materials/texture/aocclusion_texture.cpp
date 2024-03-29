/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "aocclusion_texture.h"

#include <cmath>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

void AmbientOcclusionTexture::applyOn(Intersection *intersection, Vec2f uv,
                                      Vec2f dudv) const {
  Vec2f st = this->get_st(uv);
  Vec3f ao = this->modifier.mult(this->evaluate(st));

  intersection->material.kd = intersection->material.kd.mult(ao);
};