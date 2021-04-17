/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include <tuple>
#include <vector>

#include "maths/maths.h"
#include "raytrc/geometry/bounding_volumes/aabb.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/geometry/ray.h"
#include "raytrc/materials/mapping/texture_mapping.h"
#include "raytrc/materials/material.h"
#include "raytrc/materials/texture/texture.h"

using namespace gem;

namespace raytrc {

/*!
 * @brief Objects are defined as elements with a clear position, containing
 * information about their surface structure (i.e. intersection test and
 * textures)
 */
class ObjectBase {
 public:
  Vec3f position; /*!< position of object */
  std::vector<std::tuple<std::shared_ptr<TextureMapping>, const Texture *>>
      textures; /*!< textures as tuple of mapping and actual texture */

  /*!
   * @brief Default constructor
  */
  ObjectBase() = default;

  /*!
   * @brief Object should have at least a position
   * @param position position in world space
  */
  ObjectBase(Vec3f position) : position(position){};

  
  /*!
   * @brief Calculates closest intersection in positive direction
   * @param ray ray to test
   * @param intersection intersection stub to fill with data
   * @return whether intersection (in pos direction) was found or not
  */
  virtual bool intersect(Ray *ray, Intersection *intersection) = 0;

  /*!
   * @brief Objects define their AABB themselves
   * @return new instance of AABB with proper min/max of object
  */
  virtual AABB getAABB() = 0;
};

}  // namespace raytrc