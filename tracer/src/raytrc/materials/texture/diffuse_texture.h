/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/texture/image_texture.h"
#include "raytrc/materials/texture/texture_enums.h"

using namespace gem;
using namespace cimg_library;

namespace raytrc {

/*!
 * @brief Diffuse textures apply their texture values by updating the diffuse part of the
 * material.
 */
class DiffuseTexture : public ImageTexture {
 public:
  DiffuseTexture(CImg<uint8_t> image, ImageTextureWrapMode wrapMode,
                 ImageTextureFilterMode filterMode,
                 Vec3f modifier = Vec3f(1.0f))
      : ImageTexture(image, wrapMode, filterMode, modifier){};
  DiffuseTexture(std::string file, ImageTextureWrapMode wrapMode,
                 ImageTextureFilterMode filterMode,
                 Vec3f modifier = Vec3f(1.0f))
      : ImageTexture(file, wrapMode, filterMode, modifier){};

  void applyOn(Intersection *intersection, Vec2f uv,
               Vec2f dudv = Vec2f(0.0f)) const override;
};

}  // namespace raytrc