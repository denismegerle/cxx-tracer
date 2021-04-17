#include "material.h"

namespace raytrc {

const Material Materials::METAL_RED(Vec3f(0.75f, 0.0f, 0.0f),
                                    Vec3f(0.9f, 0.0f, 0.0f),
                                    Vec3f(0.75f, 0.0f, 0.0f), Vec3f(0.0f),
                                    Vec3f(0.0f), 10);

const Material Materials::SHINY_GREEN(Vec3f(0.0f, 0.3f, 0.0f),
                                      Vec3f(0.0f, 0.6f, 0.0f),
                                      Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f),
                                      Vec3f(0.0f), 5);

const Material Materials::DIFFUSE_BLUE(Vec3f(0.0f, 0.0f, 0.1f),
                                       Vec3f(0.0f, 0.0f, 0.7f),
                                       Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f),
                                       Vec3f(0.0f), 1);

const Material Materials::REFLECTIVE_SIMPLE(Vec3f(0.05f), Vec3f(0.5f),
                                            Vec3f(0.7f), Vec3f(0.8f),
                                            Vec3f(0.0f), 3);

const Material Materials::MIRROR_SIMPLE(Vec3f(0.01f), Vec3f(0.0f), Vec3f(1.0f),
                                        Vec3f(0.99f), Vec3f(0.0f), 3);

const Material Materials::GLASS_SIMPLE(Vec3f(0.01f), Vec3f(0.1f), Vec3f(0.1f),
                                       Vec3f(0.0f), Vec3f(0.8f), 3, 2.0f);

/* materials from devernay (http://devernay.free.fr/cours/opengl/materials.html)
 */
const Material Materials::AIR(Vec3f(0.0f), Vec3f(0.0f), Vec3f(0.0f),
                              Vec3f(0.0f), Vec3f(1.0f), 0, 1.000292f);

const Material Materials::EMERALD(Vec3f(0.0215f, 0.1745f, 0.0215f),
                                  Vec3f(0.07568f, 0.61424f, 0.07568f),
                                  Vec3f(0.633f, 0.727811f, 0.633f), Vec3f(0.0f),
                                  Vec3f(0.0f), 76.8f);
const Material Materials::RUBY(Vec3f(0.1745f, 0.01175f, 0.01175f),
                               Vec3f(0.61424f, 0.04136f, 0.04136f),
                               Vec3f(0.727811f, 0.626959f, 0.626959f),
                               Vec3f(0.0f), Vec3f(0.0f), 76.8f);
const Material Materials::BRONZE(Vec3f(0.2125f, 0.1275f, 0.054f),
                                 Vec3f(0.714f, 0.4284f, 0.18144f),
                                 Vec3f(0.393548f, 0.271906f, 0.166721f),
                                 Vec3f(0.7f), Vec3f(0.0f), 25.6f);
const Material Materials::CHROME(Vec3f(0.25f, 0.25f, 0.25f),
                                 Vec3f(0.4f, 0.4f, 0.4f),
                                 Vec3f(0.774597f, 0.774597f, 0.774597f),
                                 Vec3f(0.6f), Vec3f(0.0f), 76.8f);
const Material Materials::COPPER(Vec3f(0.19125f, 0.0735f, 0.0225f),
                                 Vec3f(0.7038f, 0.27048f, 0.0828f),
                                 Vec3f(0.256777f, 0.137622f, 0.086014f),
                                 Vec3f(0.7f), Vec3f(0.0f), 17.8f);
const Material Materials::GOLD(Vec3f(0.24725f, 0.1995f, 0.0745f),
                               Vec3f(0.75164f, 0.60648f, 0.22648f),
                               Vec3f(0.628281f, 0.555802f, 0.366065f),
                               Vec3f(0.7f), Vec3f(0.0f), 12.8f);
const Material Materials::SILVER(Vec3f(0.19225f, 0.19225f, 0.19225f),
                                 Vec3f(0.50754f, 0.50754f, 0.50754f),
                                 Vec3f(0.508273f, 0.508273f, 0.508273f),
                                 Vec3f(0.9f), Vec3f(0.0f), 51.2f);
const Material Materials::CYAN_PLASTIC(Vec3f(0.0f, 0.1f, 0.06f),
                                       Vec3f(0.0f, 0.50980392f, 0.50980392f),
                                       Vec3f(0.50196078f, 0.50196078f,
                                             0.50196078f),
                                       Vec3f(0.0f), Vec3f(0.0f), 32.0f);
const Material Materials::YELLOW_PLASTIC(Vec3f(0.0f, 0.0f, 0.0f),
                                         Vec3f(0.5f, 0.5f, 0.0f),
                                         Vec3f(0.60f, 0.60f, 0.50f),
                                         Vec3f(0.0f), Vec3f(0.0f), 32.0f);
const Material Materials::BLACK_RUBBER(Vec3f(0.02f, 0.02f, 0.02f),
                                       Vec3f(0.01f, 0.01f, 0.01f),
                                       Vec3f(0.4f, 0.4f, 0.4f), Vec3f(0.0f),
                                       Vec3f(0.0f), 10.0f);
const Material Materials::WHITE_RUBBER(Vec3f(0.05f, 0.05f, 0.05f),
                                       Vec3f(0.5f, 0.5f, 0.5f),
                                       Vec3f(0.7f, 0.7f, 0.7f), Vec3f(0.0f),
                                       Vec3f(0.0f), 10.0f);

}  // namespace raytrc