/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "gloss_texture.h"

#include <cmath>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

/*!
 * The shininess is converted to the ks values using
 * shininess = pow(2.0, 13.0 * ks)
 */
void GlossTexture::applyOn(Intersection *intersection, Vec2f uv,
                           Vec2f dudv) const {
  Vec2f st = this->get_st(uv);
  Vec3f ks = this->modifier.mult(this->evaluate(st));

  float shininess = pow(2.0, 13.0 * ks[0]);

  intersection->material.n = shininess;
};