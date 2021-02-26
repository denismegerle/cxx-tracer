#pragma once

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/texture/texture.h"
#include "raytrc/texture/texture_enums.h"

using namespace gem;
using namespace cimg_library;
using namespace std;

namespace raytrc {

class ImageTexture : Texture {
 public:
  ImageTextureWrapMode wrapMode;
  ImageTextureFilterMode filterMode;

  CImg<float> image;

  ImageTexture(CImg<float> image, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode)
      : image(image), wrapMode(wrapMode), filterMode(filterMode){};
  ImageTexture(string file, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode);

  Vec3f evaluate(Vec2f uv, Vec2f dudv = Vec2f(0.0f)) const override;
};

}  // namespace raytrc