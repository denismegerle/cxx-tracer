#pragma once

#include "maths/maths.h"
#include "random.h"

namespace raytrc {

/*!
 * @brief Generates a pseudo blue noise grid by uniformly shifting from the
 * center pixel positions by a random amount.
 * @param width width, i.e. amount of pixels in x direction
 * @param height height, i.e. amount of pixels in y direction
 * @param supersamples amount of supersamples per pixel
 * @param variance bandwidth or max shift value (left max shift + right max
 * shift)
 * @return 3d array, grid of floats to be sampled (stochastic grid, randomly
 * distributed)
 */
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

/*!
 * @brief Generates a uniformly distributed grid of sample pixel positions. Each
 * pixel is subdivided into supersamples many samples, equidistant.
 * @param width width, i.e. amount of pixels in x direction
 * @param height height, i.e. amount of pixels in y direction
 * @param supersamples amount of supersamples per pixel
 * @return 3d array, grid of floats to be sampled (uniform grid, equidistant
 * samples)
 */
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