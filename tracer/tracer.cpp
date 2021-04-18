/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2021 heyitsden@github */
#include "tracer.h" /* importing all raytrc headers via this header [only here for readability] */

#include <omp.h>

#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

#include "CImg.h"
#include "config.h"
#include "maths/maths.h"
#include "stb_image_write.h"

constexpr auto PIXEL_WIDTH = 1920;
constexpr auto PIXEL_HEIGHT = 1080;
constexpr auto CHANNEL = 3;
constexpr auto DEFAULT_FOV = M_PI / 2.0f;

constexpr auto N_SUPERSAMPLES = 1;
constexpr auto SUPERSAMPLING_VARIANCE = 1.0f;

constexpr auto N_SHADOWRAYS = 1;

constexpr auto N_DEFOCUSRAYS = 1;

constexpr auto REFLECTION_ON = true;
constexpr auto TRANSMISSION_ON = true;
constexpr auto MAX_RECURSION_DEPTH = 6;

using namespace raytrc;
using namespace gem;

Vec3f raytrace(World *world, Ray *ray, int recursionDepth,
               int maxRecursionDepth);
void render(World *world, uint8_t *frameBuffer);
float gamma_correct(float color, float gamma);

int main() {
  std::cout << RESOURCES_PATH << std::endl;
  std::srand(25);

  Vec2f *sphereLocationSamples = get_sample_matrix_stochastic(10, 10, 2, 0.9f);

  /* ********** TEXTURE LOADING ********** */
  std::string tex_rock_diffuse_file(
      RESOURCES_PATH + std::string("textures/diffuse/rock_10_diffuse.jpg"));
  DiffuseTexture tex_rock_diffuse(
      tex_rock_diffuse_file, ImageTextureWrapMode::REPEAT,
      ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_rock_diffuse_mapping = std::make_shared<PlanarMapping>(
      Vec3f(0.0f), Vec2f(1.0f), Vec3f(1.0f, 0.0f, 0.0f),
      Vec3f(0.0f, 1.0f, 0.0f));

  std::string tex_rock_normal_file(
      RESOURCES_PATH + std::string("textures/normal/rock_10_normal.jpg"));
  NormalTexture tex_rock_normal(tex_rock_normal_file,
                                ImageTextureWrapMode::REPEAT,
                                ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_rock_normal_mapping = std::make_shared<PlanarMapping>(
      Vec3f(0.0f), Vec2f(1.0f), Vec3f(1.0f, 0.0f, 0.0f),
      Vec3f(0.0f, 1.0f, 0.0f));

  std::string tex_crystal_diffuse_file(
      RESOURCES_PATH + std::string("textures/diffuse/Crystal_001_COLOR.jpg"));
  DiffuseTexture tex_crystal_diffuse(
      tex_crystal_diffuse_file, ImageTextureWrapMode::REPEAT,
      ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_crystal_diffuse_mapping =
      std::make_shared<LatLngMapping>(Vec2f(1.0f));

  std::string tex_crystal_normal_file(
      RESOURCES_PATH + std::string("textures/normal/Crystal_001_NORM.jpg"));
  NormalTexture tex_crystal_normal(
      tex_crystal_normal_file, ImageTextureWrapMode::REPEAT,
      ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_crystal_normal_mapping =
      std::make_shared<LatLngMapping>(Vec2f(1.0f));

  std::string tex_crystal_specular_file(
      RESOURCES_PATH + std::string("textures/specular/Crystal_001_SPEC.jpg"));
  SpecularTexture tex_crystal_specular(
      tex_crystal_specular_file, ImageTextureWrapMode::REPEAT,
      ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_crystal_specular_mapping =
      std::make_shared<LatLngMapping>(Vec2f(1.0f));

  std::string tex_bronze_normal_file(
      RESOURCES_PATH + std::string("textures/normal/rock_11_normal.jpg"));
  NormalTexture tex_bronze_normal(
      tex_bronze_normal_file, ImageTextureWrapMode::REPEAT,
      ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_bronze_normal_mapping = std::make_shared<PlanarMapping>(
      Vec3f(0.0f), Vec2f(3.0f), Vec3f(1.0f, 0.0f, 0.0f),
      Vec3f(0.0f, 1.0f, 0.0f));

  std::string tex_environ_diffuse_file(
      RESOURCES_PATH +
      std::string("textures/environment/skybox_cube_texture.jpg"));
  EnvironmentTexture tex_environ_diffuse(
      tex_environ_diffuse_file, ImageTextureWrapMode::REPEAT,
      ImageTextureFilterMode::BILINEAR, Vec3f(1.0f));
  auto tex_environ_diffuse_mapping = std::make_shared<CubeMapping>(Vec2f(1.0f));

  /* ********** CAMERA CREATION ********** */
  Vec3f camPosition(-4.0f, 0.0f, 0.75f);
  Vec3f camTarget(-2.0f, 0.0f, 0.0f);
  Vec3f camUp(0.0f, 0.0f, 1.0f);
  float camDistanceToImagePane = 0.25f;

  Vec2f *sampleMatrix = get_sample_matrix_stochastic(
      PIXEL_WIDTH, PIXEL_HEIGHT, N_SUPERSAMPLES, SUPERSAMPLING_VARIANCE);

  /*
  std::shared_ptr<Camera> cam =
  std::make_shared<SupersamplingLenseCamera>(camPosition, camTarget, camUp,
  PIXEL_WIDTH, PIXEL_HEIGHT, camDistanceToImagePane, DEFAULT_FOV,
  N_SUPERSAMPLES, sampleMatrix, 2.25f, 0.1f);
  */
  /*
  std::shared_ptr<Camera> cam = std::make_shared<SupersamplingPinholeCamera>(
      camPosition, camTarget, camUp, PIXEL_WIDTH, PIXEL_HEIGHT,
      camDistanceToImagePane, DEFAULT_FOV, N_SUPERSAMPLES, sampleMatrix);
  */
  std::shared_ptr<Camera> cam = std::make_shared<PinholeCamera>(
      camPosition, camTarget, camUp, PIXEL_WIDTH, PIXEL_HEIGHT,
      camDistanceToImagePane, DEFAULT_FOV);

  /* ********** WORLD CREATION ********** */
  std::vector<std::shared_ptr<ObjectBase>> objects;
  std::vector<std::shared_ptr<LightSource>> lightSources;

  // ground
  auto p1 =
      std::make_shared<Plane>(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));
  /*
  auto p1_t1 = std::make_tuple(tex_rock_diffuse_mapping, &tex_rock_diffuse);
  p1->textures.push_back(p1_t1);
  auto p1_t2 = std::make_tuple(tex_rock_normal_mapping, &tex_rock_normal);
  p1->textures.push_back(p1_t2);
  */
  auto p1_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                              &ConstTextures::WHITE_RUBBER);
  p1->textures.push_back(p1_t);

  // backside
  auto p2 =
      std::make_shared<Plane>(Vec3f(5.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));
  auto p2_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                              &ConstTextures::WHITE_RUBBER);
  p2->textures.push_back(p2_t);

  objects.push_back(p1);
  objects.push_back(p2);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 2; k++) {
        float x = sphereLocationSamples[i * 2 * 10 + j * 2 + k][0] - 5.0f;
        float y = sphereLocationSamples[i * 2 * 10 + j * 2 + k][1] - 5.0f;

        auto s = std::make_shared<Sphere>(Vec3f(x, y, 0.1f), 0.1f);

        const Texture *tex;
        std::shared_ptr<TextureMapping> mpg;
        switch (k) {
          case 0:
            switch ((i + j) % 3) {
              case 0:
                tex = &ConstTextures::MIRROR_SIMPLE;
                mpg = std::make_shared<ZeroMapping>();
                break;
              case 1:
                tex = &ConstTextures::GLASS_SIMPLE;
                mpg = std::make_shared<ZeroMapping>();
                break;
              case 2:
                tex = &ConstTextures::EMERALD;
                mpg = std::make_shared<ZeroMapping>();
                break;
            }
            break;
          case 1:
            switch ((i + j) % 3) {
              case 0:
                tex = &ConstTextures::GOLD;
                mpg = std::make_shared<ZeroMapping>();
                break;
              case 1:
                tex = &ConstTextures::YELLOW_PLASTIC;
                mpg = std::make_shared<ZeroMapping>();
                break;
              case 2:
                tex = &ConstTextures::COPPER;
                mpg = std::make_shared<ZeroMapping>();
                break;
            }
            break;
        }
        // auto s_t = std::make_tuple(mpg, tex);
        auto s_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                                   &ConstTextures::WHITE_RUBBER);

        s->textures.push_back(s_t);
        objects.push_back(s);
      }
    }
  }

  auto s1 = std::make_shared<Sphere>(Vec3f(-3.0f, 1.0f, 0.5f), 0.5f);
  /*
  auto s1_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                              &ConstTextures::MIRROR_SIMPLE);
  s1->textures.push_back(s1_t);
  */
  auto s1_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                              &ConstTextures::WHITE_RUBBER);
  s1->textures.push_back(s1_t);

  auto s2 = std::make_shared<Sphere>(Vec3f(-2.0f, -0.75f, 0.5f), 0.5f);
  /*
  auto s2_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                              &ConstTextures::GLASS_SIMPLE);
  s2->textures.push_back(s2_t); */
  auto s2_t = std::make_tuple(std::make_shared<ZeroMapping>(),
                              &ConstTextures::WHITE_RUBBER);
  s2->textures.push_back(s2_t);

  auto s3 = std::make_shared<Sphere>(Vec3f(-1.5f, 0.5f, 0.5f), 0.5f);
  auto s3_t0 = std::make_tuple(std::make_shared<ZeroMapping>(),
                               &ConstTextures::WHITE_RUBBER);
  s3->textures.push_back(s3_t0);
  /*
  auto s3_t0 = std::make_tuple(std::make_shared<ZeroMapping>(),
                               &ConstTextures::GLASS_SEMI);
  s3->textures.push_back(s3_t0);
  auto s3_t1 =
      std::make_tuple(tex_crystal_diffuse_mapping, &tex_crystal_diffuse);
  s3->textures.push_back(s3_t1);
  auto s3_t2 = std::make_tuple(tex_crystal_normal_mapping, &tex_crystal_normal);
  s3->textures.push_back(s3_t2);
  auto s3_t3 =
      std::make_tuple(tex_crystal_specular_mapping, &tex_crystal_normal);
  s3->textures.push_back(s3_t3);
  */

  objects.push_back(s1);
  objects.push_back(s2);
  objects.push_back(s3);

  auto t1 = std::make_shared<Triangle>(Vec3f(-3.0f, -2.0f, 0.0f),
                                       Vec3f(-2.5f, -2.0f, 1.0f),
                                       Vec3f(-2.5f, -1.0f, 0.0f));
  auto t1_t =
      std::make_tuple(std::make_shared<ZeroMapping>(), &ConstTextures::WHITE_RUBBER);
  t1->textures.push_back(t1_t);
  /*
  auto t1_t =
      std::make_tuple(std::make_shared<ZeroMapping>(), &ConstTextures::BRONZE);
  t1->textures.push_back(t1_t);
  auto t1_t1 = std::make_tuple(tex_bronze_normal_mapping, &tex_bronze_normal);
  t1->textures.push_back(t1_t1); */

  objects.push_back(t1);

  /*
  lightSources.push_back(std::make_shared<SphereLight>(
      Vec3f(-2.5f, 0.5f, 3.0f), 10.0f, Vec3f(6.0f), Vec3f(6.0f)));
      */
  lightSources.push_back(std::make_shared<PointLight>(
      Vec3f(-2.5f, 0.5f, 3.0f), Vec3f(6.0f), Vec3f(6.0f)));
  lightSources.push_back(
      std::make_shared<AmbientLight>(Vec3f(0.0f), Vec3f(1.5f)));

  World world(cam, objects, lightSources, std::make_shared<BVH>(objects));
  //world.envTexture = &tex_environ_diffuse;
  //world.envMapping = tex_environ_diffuse_mapping;

  uint8_t *frameBuffer = new uint8_t[CHANNEL * PIXEL_WIDTH * PIXEL_HEIGHT];

  render(&world, frameBuffer);

  cimg_library::CImg<uint8_t> cimage(frameBuffer, PIXEL_WIDTH, PIXEL_HEIGHT, 1,
                                     CHANNEL);
  cimg_library::CImgDisplay disp;
  disp.display(cimage).resize(false).move(100, 100).wait(20000);
  cimage.save("raytraced.png");

  delete[] sphereLocationSamples;
  delete[] sampleMatrix;
  delete[] frameBuffer;
  return 0;
}

void render(World *world, uint8_t *frameBuffer) {
  /* ********** RT CODE ********** */
#pragma omp parallel for
  for (int y = 0; y < PIXEL_HEIGHT; y++) {
    for (int x = 0; x < PIXEL_WIDTH; x++) {
      Vec3f color(0.0f);
      for (int i = 0; i < N_SUPERSAMPLES; i++) {
        for (int j = 0; j < N_SHADOWRAYS; j++) {
          for (int k = 0; k < N_DEFOCUSRAYS; k++) {
            /* 1. GENERATE PRIMARY RAY FOR THIS PIXEL */
            Ray primaryRay = world->camera->generateRay(x, y, i);

            // raytrace recursively
            color = color +
                    (1.0f / (N_SUPERSAMPLES * N_SHADOWRAYS * N_DEFOCUSRAYS)) *
                        raytrace(world, &primaryRay, 0, MAX_RECURSION_DEPTH);

            for (int c = 0; c < CHANNEL; c++) {
              if (color.norm() != 0.0f) {
                frameBuffer[c * PIXEL_WIDTH * PIXEL_HEIGHT + y * PIXEL_WIDTH +
                            x] =
                    (uint8_t)(gamma_correct(color[c], 1.0f) * 255.0f);
              } else {
                frameBuffer[c * PIXEL_WIDTH * PIXEL_HEIGHT + y * PIXEL_WIDTH +
                            x] = 0;
              }
            }
          }
        }
      }
    }
  }
}

Vec3f raytrace(World *world, Ray *ray, int recursionDepth,
               int maxRecursionDepth) {
  Vec3f color(0.0f);

  // recursion stop condition
  if (recursionDepth > maxRecursionDepth) return color;

  /* 2. CALCULATE INTERSECTION OF RAY WITH (FIRST) WORLD OBJECT */
  Intersection i;
  if (!world->cast(ray, &i)) {
    i.normal = ray->direction;
    i.material = Material();  // saving RGB of env in material kd

    if (!world->envMapping || !world->envTexture) return Vec3f(0.0f);

    Vec2f uv = world->envMapping->get_uv(&i);
    world->envTexture->applyOn(&i, uv);

    return i.material.kd;
  }

  // compute the material parameters of the intersection point
  for (auto mapping_and_texture :
       ((ObjectBase *)i.intersectedObject)->textures) {
    auto mapping = std::get<0>(mapping_and_texture);
    auto texture = (Texture *)std::get<1>(mapping_and_texture);

    Vec2f uv = mapping->get_uv(&i);
    texture->applyOn(&i, uv);
  }

  /* 3. CALCULATE LIGHT AND SHADING */
  // direct light from the light sources
  for (auto light : world->lightSources) {
    color = color + light->computeDirectLight(world, &i);
  }

  // reflection rays, only if material is actually reflective
  if (i.material.kr.norm() > 0.0f &&
      REFLECTION_ON) {  // TODO change to isReflective method
    Ray reflect = ray->reflect(&i);
    color =
        color + i.material.kr.mult(raytrace(world, &reflect, recursionDepth + 1,
                                            maxRecursionDepth));
  }

  if (i.material.kt.norm() > 0.0f && TRANSMISSION_ON) {
    // for simplification, the assumption is: we either enter or leave a
    // material (from/to air)
    float theta_i_ = acos(ray->direction.normalize().dot(i.normal));
    float theta_i = (theta_i_ > M_PI / 2.0f) ? M_PI - theta_i_ : theta_i_;
    bool entering = theta_i_ > M_PI / 2.0f;

    float eta_1 = entering ? Materials::AIR.eta : i.material.eta;
    float eta_2 = entering ? i.material.eta : Materials::AIR.eta;
    Vec3f kt = entering ? i.material.kt : Materials::AIR.kt;

    // TIR if eta_1 > eta_2 ^ asin(eta_2 / eta_1) < theta_i
    if (eta_1 < eta_2 ||
        asin(eta_2 / eta_1) >
            theta_i) {  // if eta_1 > eta_2 total internal reflection can occur
      Ray refract = ray->refract(&i, eta_1, eta_2);

      color = color + kt.mult(raytrace(world, &refract, recursionDepth + 1,
                                       maxRecursionDepth));
    }
  }

  color = color.clamp(Vec3f(0.0f), Vec3f(1.0f));
  return color;
}

float gamma_correct(float color, float gamma) {
  return std::min(1.0f, pow(color, 1.0f / gamma));
}