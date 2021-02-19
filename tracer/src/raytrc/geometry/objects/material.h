#pragma once

#include "maths/maths.h"

using namespace gem;

namespace raytrc {

struct Material {
  Vec3f ka, kd, ks;   // elem [0,1] -> ambient, diffuse, specular
  Vec3f kr, kt;       // elem [0,1] -> reflection, transmission constant
  float n;            // elem [0,inf] -> phong exponent

  Material(Vec3f ka, Vec3f kd, Vec3f ks, Vec3f kr, Vec3f kt, float n)
      : ka(ka), kd(kd), ks(ks), kr(kr), kt(kt), n(n){};
};

/* predefined materials ... */
class Materials {
 public:
  static const int IX = 5;
  static const Material METAL_RED;
  static const Material SHINY_GREEN;
  static const Material DIFFUSE_BLUE;
  static const Material REFLECTIVE_SIMPLE;
  static const Material MIRROR_SIMPLE;

  /* materials from devernay (http://devernay.free.fr/cours/opengl/materials.html) */
  static const Material EMERALD;
  static const Material RUBY;
  static const Material BRONZE;
  static const Material CHROME;
  static const Material COPPER;
  static const Material GOLD;
  static const Material SILVER;
  static const Material CYAN_PLASTIC;
  static const Material YELLOW_PLASTIC;
  static const Material BLACK_RUBBER;
  static const Material WHITE_RUBBER;

};

}  // namespace raytrc