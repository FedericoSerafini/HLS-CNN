#include "dense.h"
#include "dense_weights.h"
#include "activ_fun.h"

#pragma GCC diagnostic ignored "-Wunused-label"

void
dense
(
  const float flat_array   [FLAT_SIZE],
  float       dense_array [DENSE_SIZE]
)
{
  dense_for_d:
  for (uint8_t d = 0U; d < DENSE_SIZE; ++d)
  {
    dense_for_f:
    for (uint16_t f = 0U; f < FLAT_SIZE; ++f)
    {
      dense_array[d] += dense_weights[f][d] * flat_array[f];
    }

    dense_array[d] += dense_biases[d];
  }
}

