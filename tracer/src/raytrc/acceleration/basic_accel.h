/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include <memory>
#include <vector>

#include "raytrc/acceleration/acceleration_structure.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

/*!
 * @brief The basic acceleration structure does not accelerate intersection
 * testing at all. Instead, all objects are tested for each ray.
 */
class BasicAccel : public AccelerationStructure {
 public:
  std::vector<std::shared_ptr<ObjectBase>>
      objects; /*!< objects of the current scene */

  /*!
   * @brief For the basic structure the list of objects is simply saved
   * @param objects list of objects of a scene
   */
  BasicAccel(std::vector<std::shared_ptr<ObjectBase>> objects)
      : objects(objects){};

  /*!
   * @brief Inefficient cycling through all objects and calculating, for each
   * object, whether an intersection is found
   * @param ray ray to intersect the scene
   * @param intersection potential intersection into which the data is written
   * @return whether intersection was found
   */
  bool cast(Ray *ray, Intersection *intersection) override;
};

}  // namespace raytrc