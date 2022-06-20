#include "dense.h"
#include "dense_weights.h"
#include "activ_fun.h"

void
dense1
(
  const float flat_image   [FLAT_SIZE],
  float       dense1_image [DENSE1_SIZE]
)
{
  uint32_t index = 0U;

  dense1_for_next_layer:
  for (uint8_t i = 0U; i < DENSE1_SIZE; ++i)
  {
    float w_sum = 0.0; // Weighted sum.

    dense1_for_prev_layer:
    for (uint16_t j = 0U; j < FLAT_SIZE; ++j)
    {
      w_sum += dense1_weights[index] * flat_image[j];
      ++index;
    }

    dense1_image[i] = relu(dense1_biases[i] + w_sum);
  }
}

void
dense2
(
  const float dense1_image [DENSE1_SIZE],
        float prediction   [DIGITS]
)
{
  float dense2_image [DENSE2_SIZE]; // To collect tmp results.
  uint32_t index = 0U;

  dense2_for_next_layer:
  for (uint8_t i = 0U; i < DENSE2_SIZE; ++i)
  {
    float w_sum = 0.0F; // Weighted sum.

    dense2_for_prev_layer:
    for (uint8_t j = 0U; j < DENSE1_SIZE; ++j)
    {
      w_sum += dense2_weights[index] * dense1_image[j];
      ++index;
    }

    dense2_image[i] = dense2_biases[i] + w_sum;
  }

  soft_max(dense2_image, prediction);
}
