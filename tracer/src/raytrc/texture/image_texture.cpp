#include "image_texture.h"

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

ImageTexture::ImageTexture(string file, ImageTextureWrapMode wrapMode,
                           ImageTextureFilterMode filterMode)
    : wrapMode(wrapMode), filterMode(filterMode) {
  image = CImg<float>(file.c_str());
};

void ImageTexture::applyOn(Intersection *intersection, Vec2f uv,
                           Vec2f dudv) const {};