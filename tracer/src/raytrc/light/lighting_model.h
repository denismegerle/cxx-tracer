/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "maths/maths.h"
#include "raytrc/geometry/intersection.h"

namespace raytrc {

/*!
 * @brief Standard Phong Lighting model but without ambient part, see
 * @link{https://en.wikipedia.org/wiki/Phong_reflection_model}
 * @param lightDirection direction of light
 * @param diffuseLight diffuse light intensity as RGB
 * @param specularLight specular light intensity as RGB
 * @param intersection intersection parameters
 * @return RGB of direct light
 */
Vec3f evaluate_phong(Vec3f lightDirection, Vec3f diffuseLight,
                     Vec3f specularLight, Intersection *intersection);

}  // namespace raytrc