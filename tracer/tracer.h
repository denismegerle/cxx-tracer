/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#pragma once

#include "raytrc/acceleration/basic_accel.h"
#include "raytrc/acceleration/bvh.h"

#include "raytrc/cameras/pinhole_camera.h"
#include "raytrc/cameras/ss_lense_camera.h"
#include "raytrc/cameras/ss_pinhole_camera.h"

#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/geometry/objects/plane.h"
#include "raytrc/geometry/objects/sphere.h"
#include "raytrc/geometry/objects/triangle.h"
#include "raytrc/geometry/ray.h"
#include "raytrc/geometry/intersection.h"

#include "raytrc/light/ambient_light.h"
#include "raytrc/light/point_light.h"
#include "raytrc/light/sphere_light.h"

#include "raytrc/materials/mapping/cube_mapping.h"
#include "raytrc/materials/mapping/latlng_mapping.h"
#include "raytrc/materials/mapping/planar_mapping.h"
#include "raytrc/materials/mapping/spherical_mapping.h"
#include "raytrc/materials/mapping/texture_mapping.h"
#include "raytrc/materials/mapping/zero_mapping.h"
#include "raytrc/materials/texture/aocclusion_texture.h"
#include "raytrc/materials/texture/const_texture.h"
#include "raytrc/materials/texture/diffuse_texture.h"
#include "raytrc/materials/texture/environment_texture.h"
#include "raytrc/materials/texture/gloss_texture.h"
#include "raytrc/materials/texture/image_texture.h"
#include "raytrc/materials/texture/normal_texture.h"
#include "raytrc/materials/texture/specular_texture.h"
#include "raytrc/materials/texture/texture.h"
#include "raytrc/materials/texture/texture_enums.h"
#include "raytrc/materials/material.h"

#include "raytrc/sampling/sampler.h"
#include "raytrc/const.h"
#include "raytrc/world.h"