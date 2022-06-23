#include "dense.hh"
#include "dense_weights.hh"
#include "activ_fun.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
dense_layer
(
  float              flat_array [FLAT_SIZE],
  hls::stream<float> prediction [DIGITS]
)
{
  float w_sum = 0.0;
  hls::stream<float> dense_array [DENSE_SIZE];

  dense_for_d:
  for (int d = 0; d < DENSE_SIZE; ++d)
  {
    w_sum = 0.0;

    dense_for_f:
    for (int f = 0; f < FLAT_SIZE; ++f)
    {
      w_sum += dense_weights[f][d] * flat_array[f];
    }

    dense_array[d].write(w_sum + dense_biases[d]);
  }

  soft_max(dense_array, prediction);
}

