/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include <vector>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/texture/texture.h"
#include "raytrc/materials/texture/texture_enums.h"

using namespace gem;
using namespace cimg_library;

namespace raytrc {

/*!
 * @brief Image textures are a special type of texture that are defined per
 * array of values (image), and can be loaded at startup from any image file.
 */
class ImageTexture : public Texture {
 public:
  bool mipMappable; /*!< whether to generate mipmap (sides power of 2) */
  Vec3f modifier;   /*!< modifier to apply after retrieval of texture */
  ImageTextureWrapMode wrapMode;
  ImageTextureFilterMode filterMode;

  CImg<uint8_t> image;                /*!< texture content */
  std::vector<CImg<uint8_t>> mipmaps; /*!< only specified if mipMappable, 0
                                         corresponds to original image */

  /*!
   * @brief Constructor that generates a image texture from an already loaded
   * image
   */
  ImageTexture(CImg<uint8_t> image, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode, Vec3f modifier = Vec3f(1.0f))
      : image(image),
        wrapMode(wrapMode),
        filterMode(filterMode),
        modifier(modifier),
        mipMappable(false){};
  /*!
   * @brief Generates image texture by specifying path to image
   * @param file string path to texture file
   */
  ImageTexture(std::string file, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode, Vec3f modifier = Vec3f(1.0f));

  /*!
   * @brief Creates the mip map by filtering 1x2, 2x1, 2x2 patches until only 1
   * pixel is left
   */
  void createMipmap() const;

  /*!
   * @brief Getting the st texture coordinates, these are always in (0,1)
   * @param uv uv coordinates, possible outside of (0,1)
   * @return st coords in (0,1)
   */
  Vec2f get_st(Vec2f uv) const;
  /*!
   * @brief Method evaluates texture based on wrap mode and filter mode
   * @param st st coordinates of point
   * @return properties of texture at/filtered at st
   */
  Vec3f evaluate(Vec2f st) const;

 private:
  Vec3f evaluateNearest(Vec2f st) const;
  Vec3f evaluateBilinear(Vec2f st) const;
};

}  // namespace raytrc