#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

namespace raytrc {

Vec3f evaluate_phong(Vec3f lightDirection, Vec3f diffuseLight, Vec3f specularLight, Intersection *intersection);

}  // namespace raytrc