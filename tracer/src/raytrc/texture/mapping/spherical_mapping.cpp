#include "spherical_mapping.h"

#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace std;

Vec2f SphericalMapping::get_uv(Intersection *intersection) const {
  Vec3f normal = (intersection->position - center).normalize();

  float m = 2.0f *
            std::sqrtf(std::powf(normal[1], 2.0f) + std::powf(normal[2], 2.0f) +
                       std::powf(1.0f + normal[0], 2.0f));

  float u = normal[1] / m + 0.5f;
  float v = normal[2] / m + 0.5f;

  return scale.mult(Vec2f(u, v));
}
