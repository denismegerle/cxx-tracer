#include <cmath>

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "latlng_mapping.h"

using namespace raytrc;
using namespace std;

Vec2f LatLngMapping::get_uv(Intersection *intersection) const {
  float azimuth = atan2(intersection->normal[1], intersection->normal[0]);
  float polar = acos(intersection->normal[2]);

  float u = 0.5f + azimuth / (2.0f * M_PI);
  float v = polar / M_PI;

  return scale.mult(Vec2f(u, v));
}
