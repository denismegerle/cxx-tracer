/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"

namespace raytrc {

/*!
 * @brief Acceleration structure to search for intersection points in multiple
 * objects in a scene.
 *
 * The structure must define a cast function, and should store all objects of a
 * scene. *
 */
class AccelerationStructure {
 public:
  /*!
   * @brief Casting the given ray through the scene, searching for intersections
   *        in the scene geometry
   * @param ray ray to be cast
   * @param intersection pointer to empty intersection that can be filled with
   *        information
   * @return whether intersection found
  */
  virtual bool cast(Ray *ray, Intersection *intersection) = 0;
};

}  // namespace raytrc
