
#include "plane.h"

#include "raytrc/geometry/objects/aabb.h"

using namespace raytrc;

// needs to return closest intersection point!
bool Plane::intersect(Ray *ray, Intersection *intersection) {
  float relativeOrientation =
      ray->direction.normalize() * this->normal;  // normal already normalized

  if (relativeOrientation != 0) {  // not parallel -> definitely intersecting,
                                   // case parallel + inf intersections ignored.
    float t = (this->normal * this->position - ray->origin * this->normal) /
              relativeOrientation;  // = (d - E * N) / (D * N)

    ray->t = t / ray->direction.norm();

    intersection->intersectedObject = this;
    intersection->position = ray->equate();
    intersection->normal = ((ray->origin - this->position) * this->normal > 0) ? this->normal.normalize() : -1.0f * this->normal.normalize();
    intersection->negRayVector =
        (ray->origin - intersection->position).normalize();
    //intersection->material = this->material;

    return true;
  }
  return false;
}

AABB Plane::getAABB() { return AABB(); };