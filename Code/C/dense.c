#include "dense.h"
#include "dense_weights.h"
#include "activ_fun.h"

void
dense1
(
  const float flat_array   [FLAT_SIZE],
  float       dense1_array [DENSE1_SIZE]
)
{

  for (uint16_t f = 0U; f < FLAT_SIZE; ++f)
  {
    for (uint8_t d = 0U; d < DENSE1_SIZE; ++d)
    {
      dense1_array[d] += dense1_weights[f][d] * flat_array[f];
    }

  }
}

void relu_on_dense1
(
  const float dense1_array[DENSE1_SIZE], float dense1_relu[DENSE1_SIZE]
)
{
  for (uint8_t i = 0U; i < DENSE1_SIZE; ++i)
  {
    dense1_relu[i] = relu(dense1_array[i] + dense1_biases[i]);
  }
}

void
dense2
(
  const float dense1_array [DENSE1_SIZE],
        float dense2_array [DIGITS]
)
{
  uint32_t index = 0U;

  #ifdef __SYNTHESYS__
  dense2_for_next_layer:
  #endif
  for (uint8_t i = 0U; i < DENSE2_SIZE; ++i)
  {
    float w_sum = 0.0F; // Weighted sum.

    #ifdef __SYNTHESYS__
    dense2_for_prev_layer:
    #endif
    for (uint8_t j = 0U; j < DENSE1_SIZE; ++j)
    {
      w_sum += dense2_weights[j][i] * dense1_array[j];
      ++index;
    }

    dense2_array[i] = dense2_biases[i] + w_sum;
  }

}
