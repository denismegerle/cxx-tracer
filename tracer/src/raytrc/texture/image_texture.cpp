#include "image_texture.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

inline float fqmodf(float a, float b) {
  float c = std::fmodf(a, b);
  return (c > 0) ? c : b - c;
}

inline Vec3f get_n_rgb_from_cimg(const CImg<uint8_t>* image, int x, int y) {
  float r, g, b;

  if (image->spectrum() == 3) {
    r = (*image)(x, y, 0, 0);
    g = (*image)(x, y, 0, 1);
    b = (*image)(x, y, 0, 2);
  } else if(image->spectrum() == 1) {
    r = (*image)(x, y, 0, 0);
    g = (*image)(x, y, 0, 0);
    b = (*image)(x, y, 0, 0);
  }

  return (1.0f / 255.0f) * Vec3f(r, g, b);
}

ImageTexture::ImageTexture(string file, ImageTextureWrapMode wrapMode,
                           ImageTextureFilterMode filterMode, Vec3f modifier)
    : wrapMode(wrapMode), filterMode(filterMode), modifier(modifier) {
  image = CImg<uint8_t>(file.c_str());
};

Vec2f ImageTexture::get_st(Vec2f uv) const {
  Vec2f st;

  switch (this->wrapMode) {
    case ImageTextureWrapMode::REPEAT:
      st[0] = fqmodf(uv[0], 1.0f);
      st[1] = fqmodf(uv[1], 1.0f);
      break;
    case ImageTextureWrapMode::CLAMP:
      st[0] = std::clamp(uv[0], 0.0f, 1.0f);
      st[1] = std::clamp(uv[1], 0.0f, 1.0f);
      break;
    case ImageTextureWrapMode::ZERO:
      st[0] = (uv[0] < 0.0f || uv[0] > 1.0f) ? 0.0f : uv[0];
      st[1] = (uv[1] < 0.0f || uv[1] > 1.0f) ? 0.0f : uv[1];
      break;
  }

  st = st.mult(Vec2f((float)(this->image.width() - 1),
                     (float)(this->image.height() - 1)));
  return st;
};

Vec3f ImageTexture::evaluate(Vec2f st) const {
  switch (filterMode) {
    case ImageTextureFilterMode::NEAREST:
      return evaluateNearest(st);
    case ImageTextureFilterMode::BILINEAR:
      return evaluateBilinear(st);
  }
}

Vec3f ImageTexture::evaluateNearest(Vec2f st) const {
  int x = std::roundf(st[0]);
  int y = std::roundf(st[1]);

  return get_n_rgb_from_cimg(&(this->image), x, y);
}

Vec3f ImageTexture::evaluateBilinear(Vec2f st) const {
  int x_floor = std::floorf(st[0]);
  int y_floor = std::floorf(st[1]);
  int x_ceil = std::ceilf(st[0]);
  int y_ceil = std::ceilf(st[1]);

  Vec3f rgb1 = get_n_rgb_from_cimg(&(this->image), x_floor, y_floor);
  Vec3f rgb2 = get_n_rgb_from_cimg(&(this->image), x_ceil, y_floor);
  Vec3f rgb3 = get_n_rgb_from_cimg(&(this->image), x_floor, y_ceil);
  Vec3f rgb4 = get_n_rgb_from_cimg(&(this->image), x_ceil, y_ceil);

  float a = std::fmodf(st[0], 1.0f);
  float b = std::fmodf(st[1], 1.0f);

  Vec3f rgb12 = (1 - a) * rgb1 + a * rgb2;
  Vec3f rgb34 = (1 - a) * rgb3 + a * rgb4;
  Vec3f rgb = (1 - b) * rgb12 + b * rgb34;
  return rgb;
}