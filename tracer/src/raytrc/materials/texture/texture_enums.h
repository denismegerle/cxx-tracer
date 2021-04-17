/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

namespace raytrc {

/*!
 * @brief Texture Filtering according to this mode.
 * Bilinear = linear per dimension, then linear
 * Nearest = non filtered
 */
enum ImageTextureFilterMode { NEAREST, BILINEAR };

/*!
 * @brief Wrap modes for textures define how uv coordinates outside (0, 1) are
 * mapped
 * Repeat = modulo back into (0, 1)
 * Clamp = set to 0 / 1 if outside
 * Zero = 0
 */
enum ImageTextureWrapMode { REPEAT, CLAMP, ZERO };

}  // namespace raytrc
