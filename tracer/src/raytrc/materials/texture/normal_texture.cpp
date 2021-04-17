#include "normal_texture.h"

#include <cmath>

#include "CImg.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace gem;
using namespace cimg_library;

void NormalTexture::applyOn(Intersection *intersection, Vec2f uv,
                            Vec2f dudv) const {
  Vec2f st = this->get_st(uv);
  Vec3f tangent_space_normal =
      (2.0f * (this->evaluate(st) - Vec3f(0.5f))).normalize();

  Vec3f T = intersection->normal.cross(Vec3f(0.0f, 0.0f, 1.0f)).normalize();
  if (T.norm() == 0.0f) T = Vec3f(0.0f, 1.0f, 0.0f);
  Vec3f B = intersection->normal.cross(T).normalize();
  Vec3f N = intersection->normal.normalize();

  // P von T -> W : R_uvw^T * P wobei R_uvw = (u^T, v^T, w^T) und u,v,w
  // Orth.Normale Basisvektoren des Tangentensystems im Weltsystem [-> da
  // Orth.Normale Vektoren ist (M^-1)^T * N = M * N ]
  Mat3f tbn(T[0], B[0], N[0], T[1], B[1], N[1], T[2], B[2], N[2]);

  intersection->normal = (tbn * tangent_space_normal).normalize();
};