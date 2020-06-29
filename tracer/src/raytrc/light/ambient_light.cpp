
#include "ambient_light.h"
#include "raytrc/world.h"

using namespace raytrc;
using namespace gem;

/*

*/
Vec3f AmbientLight::computeDirectLight(World *world, Intersection *intersection) {
  return intensity;
}