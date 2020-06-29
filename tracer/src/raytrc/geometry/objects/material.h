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
extern Material MATERIAL_BASIC;
extern Material MATERIAL_METAL_RED;
extern Material MATERIAL_SHINY_GREEN;
extern Material MATERIAL_DIFFUSE_BLUE;
extern Material MATERIAL_REFLECTIVE_SIMPLE;

}  // namespace raytrc