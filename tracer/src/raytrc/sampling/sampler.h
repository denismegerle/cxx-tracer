#pragma once

#include "maths/maths.h"

#include "random.h"

namespace raytrc {

Vec2f *get_sample_matrix_stochastic(int width, int height, int supersamples,
                                 float variance) {
  Vec2f *sampleMatrix = new Vec2f[width * height * supersamples];

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      for (int s = 0; s < supersamples; s++) {
        sampleMatrix[x * supersamples * height + y * supersamples + s] =
            Vec2f(x + variance * ((float)random_double() - 0.5f),
                  y + variance * ((float)random_double() - 0.5f));
      }
    }
  }

  return sampleMatrix;
}

Vec2f *get_sample_matrix_uniform(int width, int height, int supersamples) {
  Vec2f *sampleMatrix = new Vec2f[width * height * supersamples];

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      for (int s = 0; s < supersamples; s++) {
        sampleMatrix[x * supersamples * height + y * supersamples + s] =
            Vec2f(x + s / (float)supersamples, y + s / (float)supersamples);
      }
    }
  }

  return sampleMatrix;
}

}  // namespace raytrc