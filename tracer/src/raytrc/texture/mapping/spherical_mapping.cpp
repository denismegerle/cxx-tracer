#include "spherical_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace std;

Vec2f SphericalMapping::get_uv(Intersection *intersection) const {
  Vec3f N = (intersection->position - center).normalize();
  Vec3f R = 2.0f * (intersection->normal * (intersection->negRayVector)) * intersection->normal - (intersection->negRayVector);
  R = R.normalize();

  float m = 2.0f * std::sqrtf(std::powf(R[0], 2.0f) + std::powf(R[1], 2.0f) +
                        std::powf(1.0f + R[2], 2.0f));

  float u = R[0] / m + 0.5f;
  float v = R[1] / m + 0.5f;

  return scale.mult(Vec2f(u, v));
}
