/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"
#include "raytrc/materials/mapping/texture_mapping.h"

namespace raytrc {

/*!
 * @brief Planar mapping, i.e. texture will be mapped based on two principal
 * component vectors.
 */
class PlanarMapping : public TextureMapping {
 public:
  Vec3f position;       /*!< position of texture in world space */
  Vec2f scale;          /*!< scale of texture */
  Vec3f s_axis, t_axis; /*!< s, t axis, along which to map the texture */

  /*!
   * @brief Planar mapping specifies one variable (orthogonal to the two axis)
   * along which the texture is mapped (along the plane)
   * @param position central position of the texture
   * @param scale texture scale
   * @param s_axis axis 1 along which to map
   * @param t_axis axis 2 along which to map
   */
  PlanarMapping(Vec3f position, Vec2f scale, Vec3f s_axis, Vec3f t_axis)
      : position(position), scale(scale), s_axis(s_axis), t_axis(t_axis){};

  /*!
   * @brief Computes the uv value along the two axis
   * @param intersection intersection with parameters
   * @return uv coordinates in (-inf, +inf)
  */
  Vec2f get_uv(Intersection *intersection) const override;
};

}  // namespace raytrc