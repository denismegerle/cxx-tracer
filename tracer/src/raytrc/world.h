#pragma once

#include <list>

#include "raytrc/geometry/objects/object_base.h"
#include "raytrc/light/light_source.h"

// TODO add camera in here...

namespace raytrc {

class World {
 public:
  Camera *camera;
  std::list<ObjectBase*> objects;
  std::list<LightSource*> lightSources;

  World(){};
  World(Camera *camera, std::list<ObjectBase*> objects,
        std::list<LightSource*> lightSources)
      : camera(camera), objects(objects), lightSources(lightSources){};
  
  bool cast(Ray *ray);
};

}
