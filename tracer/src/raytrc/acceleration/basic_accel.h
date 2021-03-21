#pragma once

#include <memory>
#include <vector>

#include "raytrc/acceleration/acceleration_structure.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

class BasicAccel : public AccelerationStructure {
 public:
  std::vector<std::shared_ptr<ObjectBase>> objects;

  BasicAccel(std::vector<std::shared_ptr<ObjectBase>> objects)
      : objects(objects){};

  bool cast(Ray *ray, Intersection *intersection) override;
};

}  // namespace raytrc