#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/texture/texture.h"

using namespace gem;
using namespace std;

namespace raytrc {

class ConstTexture : Texture {
 public:
  Vec3f ka, kd, ks;  // elem [0,1] -> ambient, diffuse, specular
  Vec3f kr, kt;      // elem [0,1] -> reflection, transmission constant
  float n;           // elem [0,inf] -> phong exponent
  float eta;  // refractive index [technically dependent on lambda, but we
              // assume const for now]

  ConstTexture(Vec3f ka, Vec3f kd, Vec3f ks, float n)
      : ka(ka),
        kd(kd),
        ks(ks),
        kr(Vec3f(0.0f)),
        kt(Vec3f(0.0f)),
        n(n),
        eta(0.0f){};
  ConstTexture(Vec3f ka, Vec3f kd, Vec3f ks, Vec3f kr, Vec3f kt, float n)
      : ka(ka), kd(kd), ks(ks), kr(kr), kt(kt), n(n), eta(0.0f){};
  ConstTexture(Vec3f ka, Vec3f kd, Vec3f ks, Vec3f kr, Vec3f kt, float n,
               float eta)
      : ka(ka), kd(kd), ks(ks), kr(kr), kt(kt), n(n), eta(eta){};

  void applyOn(Intersection *intersection, Vec2f uv,
               Vec2f dudv = Vec2f(0.0f)) const override;
};

class ConstTextures {
 public:
  static const ConstTexture METAL_RED;
  static const ConstTexture SHINY_GREEN;
  static const ConstTexture DIFFUSE_BLUE;
  static const ConstTexture REFLECTIVE_SIMPLE;
  static const ConstTexture MIRROR_SIMPLE;
  static const ConstTexture GLASS_SIMPLE;

  /* materials from devernay
   * (http://devernay.free.fr/cours/opengl/materials.html) */
  static const ConstTexture AIR;
  static const ConstTexture EMERALD;
  static const ConstTexture RUBY;
  static const ConstTexture BRONZE;
  static const ConstTexture CHROME;
  static const ConstTexture COPPER;
  static const ConstTexture GOLD;
  static const ConstTexture SILVER;
  static const ConstTexture CYAN_PLASTIC;
  static const ConstTexture YELLOW_PLASTIC;
  static const ConstTexture BLACK_RUBBER;
  static const ConstTexture WHITE_RUBBER;
};

}  // namespace raytrc