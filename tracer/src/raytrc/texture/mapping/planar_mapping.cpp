#include <cmath>

#include "planar_mapping.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace std;

Vec2f PlanarMapping::get_uv(Intersection *intersection) const {
  float u = (intersection->position - this->position) * s_axis;
  float v = (intersection->position - this->position) * t_axis;

  return scale.mult(Vec2f(u, v));
}
