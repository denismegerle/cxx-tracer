#pragma once

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/texture/image_texture.h"
#include "raytrc/texture/texture_enums.h"

using namespace gem;
using namespace cimg_library;
using namespace std;

namespace raytrc {

class NormalTexture : public ImageTexture {
 public:
  NormalTexture(CImg<uint8_t> image, ImageTextureWrapMode wrapMode,
                 ImageTextureFilterMode filterMode,
                 Vec3f modifier = Vec3f(1.0f))
      : ImageTexture(image, wrapMode, filterMode, modifier){};
  NormalTexture(string file, ImageTextureWrapMode wrapMode,
                 ImageTextureFilterMode filterMode,
                 Vec3f modifier = Vec3f(1.0f))
      : ImageTexture(file, wrapMode, filterMode, modifier){};

  void applyOn(Intersection *intersection, Vec2f uv,
               Vec2f dudv = Vec2f(0.0f)) const override;
};

}  // namespace raytrc