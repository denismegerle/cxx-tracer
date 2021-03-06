#pragma once

#include "CImg.h"

#include "maths/maths.h"

#include "raytrc/texture/texture.h"
#include "raytrc/texture/texture_enums.h"
#include "raytrc/geometry/intersection.h"

using namespace gem;
using namespace cimg_library;
using namespace std;

namespace raytrc {

class ImageTexture : public Texture {
 public:
  Vec3f modifier;
  ImageTextureWrapMode wrapMode;
  ImageTextureFilterMode filterMode;

  CImg<uint8_t> image;

  ImageTexture(CImg<uint8_t> image, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode, Vec3f modifier = Vec3f(1.0f))
      : image(image), wrapMode(wrapMode), filterMode(filterMode), modifier(modifier){};
  ImageTexture(string file, ImageTextureWrapMode wrapMode,
               ImageTextureFilterMode filterMode, Vec3f modifier = Vec3f(1.0f));

  Vec2f get_st(Vec2f uv) const;
  Vec3f evaluate(Vec2f st) const;
  Vec3f evaluateNearest(Vec2f st) const;
  Vec3f evaluateBilinear(Vec2f st) const;
};

}  // namespace raytrc