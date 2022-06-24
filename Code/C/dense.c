#include "dense.h"
#include "dense_weights.h"
#include "activ_fun.h"

void
dense_layer
(
  float flat_array  [FLAT_SIZE],
  float prediction [DIGITS]
)
{
  float w_sum = 0.0;
  float dense_array [DENSE_SIZE] = { 0 };

  for (int d = 0; d < DENSE_SIZE; ++d)
  {
    w_sum = 0.0;

    for (int f = 0; f < FLAT_SIZE; ++f)
    {
      w_sum += dense_weights[f][d] * flat_array[f];
    }

    dense_array[d] = w_sum + dense_biases[d];
  }

  soft_max(dense_array, prediction);
}

