# CXX-Tracer

This is a small, educational project in C++ to get familiar with the language on a deeper level.

Used concepts:
- C++ (basics, object orientation specifics, templates, project setups, ...)
- OMP/SIMD
- CMake (setup, inclusion and generation of libraries, fetching, ...)
- (Doxygen, Docker, Sphinx, ...?)


## Implemented Features
This project implements a custom ray tracer providing many features, with a simple own maths/vector library.

### Objects
Implemented are planes, spheres and triangles. Easily extensible by just defining the appropriate intersection test and an objects axis-aligned bounding box per object.

<img align="right" width="192" height="108" src="images/features_1_objects.png">

### TODO5 textures and mappings
- same texture different mapping (two to three objects)
- as an example normal and diffuse texture mapping

### TODO7 environment
- environment mapping with image/smth

### TODO4 lights
- point vs sphere lighting, i.e. soft shadows

### TODO2 cameras
- supersampling vs pinhole and additional focus lense camera

### TODO8 sampling
- same ray amount with different sampling matrices (uniform vs stochastic)

### TODO1 acceleration structures
- bvh vs normal time comparison in complex scene











## Future Work
- make transmission (in shadow rays) depth dependent instead of binary
- additional acceleration structure (kd-trees for instance)
- add trilinear filtering, anisotropic filtering and mip mapping
- add environment map filtering
- procedural textures, noise textures for cloud and mountain generation


## References
- ...
- panorama_cube_map : https://www.google.com/url?sa=i&url=https%3A%2F%2Fcommons.wikimedia.org%2Fwiki%2FFile%3APanorama_cube_map.png&psig=AOvVaw1OdJwUL-2OsaZ9N5zPg4gf&ust=1618777477752000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCKD1xKGOhvACFQAAAAAdAAAAABAD


## TODO
- add documentation generation via (xyz idk which stuff)
- maybe docker?
- add references
- cleanup rest of repo and publish