#pragma once

#include <vector>

#include "raytrc/acceleration/bvh.h"
#include "raytrc/geometry/cameras/camera.h"
#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/light/light_source.h"

namespace raytrc {

class World {
 public:
  Camera *camera;
  std::vector<std::shared_ptr<ObjectBase>> objects;
  std::vector<std::shared_ptr<LightSource>> lightSources;
  Texture *envTexture;
  std::shared_ptr<TextureMapping> envMapping;

  BVH bvh;

  World(Camera *camera, std::vector<std::shared_ptr<ObjectBase>> objects,
        std::vector<std::shared_ptr<LightSource>> lightSources)
      : camera(camera),
        objects(objects),
        lightSources(lightSources),
        bvh(BVH(objects)){};

  bool cast(Ray *ray, Intersection *intersection);
  Vec3f deriveTransmissionFactor(Ray *ray);
};

}  // namespace raytrc
