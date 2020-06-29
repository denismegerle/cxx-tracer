
#include "material.h"

/* predefined materials implementation ... */
namespace raytrc {

Material MATERIAL_BASIC(Vec3f(0.4f), Vec3f(0.1f), Vec3f(0.2f), Vec3f(0.0f),
                        Vec3f(0.0f), 3);

Material MATERIAL_METAL_RED(Vec3f(0.7f, 0.0f, 0.0f), Vec3f(0.75f, 0.0f, 0.0f),
                            Vec3f(0.75f, 0.0f, 0.0f), Vec3f(0.0f), Vec3f(0.0f),
                            10);

Material MATERIAL_SHINY_GREEN(Vec3f(0.0f, 0.3f, 0.0f), Vec3f(0.0f, 0.6f, 0.0f),
                              Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f), Vec3f(0.0f),
                              5);

Material MATERIAL_DIFFUSE_BLUE(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.0f, 0.0f, 0.7f),
                               Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f),
                               Vec3f(0.0f), 1);

Material MATERIAL_REFLECTIVE_SIMPLE(Vec3f(0.1f), Vec3f(0.5f), Vec3f(0.0f),
                                    Vec3f(0.8f), Vec3f(0.0f), 3);
}  // namespace raytrc
