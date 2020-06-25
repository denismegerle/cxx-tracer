#pragma once

#include <vector>

#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/light/light_source.h"
#include "raytrc/geometry/cameras/camera.h"

namespace raytrc {

class World {
 public:
  Camera *camera;
  std::vector<ObjectBase *> objects;
  std::vector<LightSource *> lightSources;

  World(){};
  World(Camera *camera, std::vector<ObjectBase *> objects,
        std::vector<LightSource *> lightSources)
      : camera(camera), objects(objects), lightSources(lightSources){};
  
  bool cast(Ray *ray, Intersection *intersection);
  Vec3f deriveTransmissionFactor(Ray *ray);

};

}
