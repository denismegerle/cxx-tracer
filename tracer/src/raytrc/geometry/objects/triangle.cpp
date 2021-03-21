#include "triangle.h"

#include "raytrc/geometry/objects/aabb.h"
#include "raytrc/geometry/ray.h"
#include "raytrc/geometry/intersection.h"

using namespace raytrc;

// needs to return closest intersection point!
bool Triangle::intersect(Ray *ray, Intersection *intersection) {
  // test from https://www.iquilezles.org/www/articles/intersectors/intersectors.htm
  Vec3f v1v0 = v1 - v0;
  Vec3f v2v0 = v2 - v0;
  Vec3f rov0 = ray->origin - v0;
  Vec3f n = v1v0.cross(v2v0);
  Vec3f q = rov0.cross(ray->direction);
  float d = 1.0 / (ray->direction * n);
  float u = d * (-q * v2v0);
  float v = d * (q * v1v0);
  float t = d * (-n * rov0);
  if (u < 0.0 || u > 1.0 || v < 0.0 || (u + v) > 1.0) t = -1.0;

  if (t < 0.0f) return false;

  ray->t = t;

  intersection->intersectedObject = this;
  intersection->position = ray->equate();
  intersection->normal = n.normalize();
  intersection->negRayVector =
      (ray->origin - intersection->position).normalize();

  return true;
}

AABB Triangle::getAABB() {
  Vec3f min, max;

  for (int i = 0; i < 3; i++) {
    min[i] = std::min({v0[i], v1[i], v2[i]});
    max[i] = std::max({v0[i], v1[i], v2[i]});
  }
  
  return AABB(min, max);
};