/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */ 
#pragma once

#include "CImg.h"

#include "maths/maths.h"

#include <vector>

#include "raytrc/materials/texture/texture.h"
#include "raytrc/materials/texture/texture_enums.h"
#include "raytrc/geometry/intersection.h"

using namespace gem;
using namespace cimg_library;

namespace raytrc {

class ImageTexture : public Texture {
 public:
  bool mipMappable;
  Vec3f modifier;
  ImageTextureWrapMode wrapMode;
  ImageTextureFilterMode filterMode;

  CImg<uint8_t> image;
  std::vector<CImg<uint8_t>> mipmaps;

  ImageTexture(CImg<uint8_t> image, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode, Vec3f modifier = Vec3f(1.0f))
      : image(image), wrapMode(wrapMode), filterMode(filterMode), modifier(modifier){};
  ImageTexture(std::string file, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode, Vec3f modifier = Vec3f(1.0f));

  void createMipmap() const;

  Vec2f get_st(Vec2f uv) const;
  Vec3f evaluate(Vec2f st) const;
  Vec3f evaluateNearest(Vec2f st) const;
  Vec3f evaluateBilinear(Vec2f st) const;
};

}  // namespace raytrc