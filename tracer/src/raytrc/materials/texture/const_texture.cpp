/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "const_texture.h"

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;

void ConstTexture::applyOn(Intersection *intersection, Vec2f uv,
                           Vec2f dudv) const {
  intersection->material.ka = this->ka;
  intersection->material.kd = this->kd;
  intersection->material.ks = this->ks;
  intersection->material.n = this->n;

  intersection->material.kr = this->kr;
  intersection->material.kt = this->kt;
  intersection->material.eta = this->eta;
};

const ConstTexture ConstTextures::METAL_RED(Vec3f(0.75f, 0.0f, 0.0f),
                                    Vec3f(0.9f, 0.0f, 0.0f),
                                    Vec3f(0.75f, 0.0f, 0.0f), Vec3f(0.0f),
                                    Vec3f(0.0f), 10);

const ConstTexture ConstTextures::SHINY_GREEN(Vec3f(0.0f, 0.3f, 0.0f),
                                      Vec3f(0.0f, 0.6f, 0.0f),
                                      Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f),
                                      Vec3f(0.0f), 5);

const ConstTexture ConstTextures::DIFFUSE_BLUE(Vec3f(0.0f, 0.0f, 0.1f),
                                       Vec3f(0.0f, 0.0f, 0.7f),
                                       Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f),
                                       Vec3f(0.0f), 1);

const ConstTexture ConstTextures::REFLECTIVE_SIMPLE(Vec3f(0.05f), Vec3f(0.5f),
                                            Vec3f(0.7f), Vec3f(0.8f),
                                            Vec3f(0.0f), 3);

const ConstTexture ConstTextures::MIRROR_SIMPLE(Vec3f(0.01f), Vec3f(0.0f), Vec3f(1.0f),
                                        Vec3f(0.99f), Vec3f(0.0f), 3);

const ConstTexture ConstTextures::GLASS_SIMPLE(Vec3f(0.01f), Vec3f(0.1f), Vec3f(0.1f),
                                       Vec3f(0.0f), Vec3f(0.8f), 3, 2.0f);

/* materials from devernay (http://devernay.free.fr/cours/opengl/materials.html)
 */
const ConstTexture ConstTextures::AIR(Vec3f(0.0f), Vec3f(0.0f), Vec3f(0.0f),
                              Vec3f(0.0f), Vec3f(1.0f), 0, 1.000292f);

const ConstTexture ConstTextures::EMERALD(Vec3f(0.0215f, 0.1745f, 0.0215f),
                                  Vec3f(0.07568f, 0.61424f, 0.07568f),
                                  Vec3f(0.633f, 0.727811f, 0.633f), Vec3f(0.0f),
                                  Vec3f(0.0f), 76.8f);
const ConstTexture ConstTextures::RUBY(Vec3f(0.1745f, 0.01175f, 0.01175f),
                               Vec3f(0.61424f, 0.04136f, 0.04136f),
                               Vec3f(0.727811f, 0.626959f, 0.626959f),
                               Vec3f(0.0f), Vec3f(0.0f), 76.8f);
const ConstTexture ConstTextures::BRONZE(Vec3f(0.2125f, 0.1275f, 0.054f),
                                 Vec3f(0.714f, 0.4284f, 0.18144f),
                                 Vec3f(0.393548f, 0.271906f, 0.166721f),
                                 Vec3f(0.7f), Vec3f(0.0f), 25.6f);
const ConstTexture ConstTextures::CHROME(Vec3f(0.25f, 0.25f, 0.25f),
                                 Vec3f(0.4f, 0.4f, 0.4f),
                                 Vec3f(0.774597f, 0.774597f, 0.774597f),
                                 Vec3f(0.6f), Vec3f(0.0f), 76.8f);
const ConstTexture ConstTextures::COPPER(Vec3f(0.19125f, 0.0735f, 0.0225f),
                                 Vec3f(0.7038f, 0.27048f, 0.0828f),
                                 Vec3f(0.256777f, 0.137622f, 0.086014f),
                                 Vec3f(0.7f), Vec3f(0.0f), 17.8f);
const ConstTexture ConstTextures::GOLD(Vec3f(0.24725f, 0.1995f, 0.0745f),
                               Vec3f(0.75164f, 0.60648f, 0.22648f),
                               Vec3f(0.628281f, 0.555802f, 0.366065f),
                               Vec3f(0.7f), Vec3f(0.0f), 12.8f);
const ConstTexture ConstTextures::SILVER(Vec3f(0.19225f, 0.19225f, 0.19225f),
                                 Vec3f(0.50754f, 0.50754f, 0.50754f),
                                 Vec3f(0.508273f, 0.508273f, 0.508273f),
                                 Vec3f(0.9f), Vec3f(0.0f), 51.2f);
const ConstTexture ConstTextures::CYAN_PLASTIC(Vec3f(0.0f, 0.1f, 0.06f),
                                       Vec3f(0.0f, 0.50980392f, 0.50980392f),
                                       Vec3f(0.50196078f, 0.50196078f,
                                             0.50196078f),
                                       Vec3f(0.0f), Vec3f(0.0f), 32.0f);
const ConstTexture ConstTextures::YELLOW_PLASTIC(Vec3f(0.0f, 0.0f, 0.0f),
                                         Vec3f(0.5f, 0.5f, 0.0f),
                                         Vec3f(0.60f, 0.60f, 0.50f),
                                         Vec3f(0.0f), Vec3f(0.0f), 32.0f);
const ConstTexture ConstTextures::BLACK_RUBBER(Vec3f(0.02f, 0.02f, 0.02f),
                                       Vec3f(0.01f, 0.01f, 0.01f),
                                       Vec3f(0.4f, 0.4f, 0.4f), Vec3f(0.0f),
                                       Vec3f(0.0f), 10.0f);
const ConstTexture ConstTextures::WHITE_RUBBER(Vec3f(0.05f, 0.05f, 0.05f),
                                       Vec3f(0.5f, 0.5f, 0.5f),
                                       Vec3f(0.7f, 0.7f, 0.7f), Vec3f(0.0f),
                                       Vec3f(0.0f), 10.0f);