#include "image_texture.h"

#include "CImg.h"
#include "maths/maths.h"


using namespace raytrc;
using namespace gem;
using namespace cimg_library;

ImageTexture::ImageTexture(string file, ImageTextureWrapMode wrapMode,
                           ImageTextureFilterMode filterMode)
    : wrapMode(wrapMode), filterMode(filterMode) {
  image = CImg<float>(file.c_str());
};

Vec3f ImageTexture::evaluate(Vec2f uv, Vec2f dudv) const {
  return Vec3f(0.0f);
};