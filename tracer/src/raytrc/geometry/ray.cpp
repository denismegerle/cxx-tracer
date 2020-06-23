
#include "ray.h"

using namespace raytrc;
using namespace gem;

Vec3f Ray::equate() { return this->origin + this->t * this->direction; }