#include <cmath>

#include "cube_mapping.h"
#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;
using namespace std;

Vec2f CubeMapping::get_uv(Intersection *intersection) const {
  return Vec2f(0.0f);
}
