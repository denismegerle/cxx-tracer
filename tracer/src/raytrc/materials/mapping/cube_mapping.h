/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

/*!
 * @brief Cube mapping maps the coordinate of the object, relative to its
 * center, to the point the normal would intersect if a cube was around that
 * object. For more information, see
 * @link{https://en.wikipedia.org/wiki/Cube_mapping}
 */
class CubeMapping : public TextureMapping {
 public:
  Vec2f scale; /*!< scale for mapping */

  /*!
   * @brief Basic constructor for cube mapping
   * @param scale scale of texture
   */
  CubeMapping(Vec2f scale) : scale(scale){};

  /*!
   * @brief Calculates uv coordinates, always in [0, 1] for cube mapping. Each
   * face of an object encompassing cube is defined to be in a 3x4 image, the
   * appropriate region is selected (see submethod) and relative to that, the
   * intersection point of the normal and that face defines the uv coordinates
   * (=st coordinates in cube mapping)
   * @param intersection intersection and parameters
   * @return uv coordinates, always in [0, 1] for ONE image, 3x4 regions, each
   * region defining one cube face (see example cube map)
   */
  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc