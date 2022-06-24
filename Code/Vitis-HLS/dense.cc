#include "dense.hh"
#include "activ_fun.hh"
#include "../Headers/dense_weights.h"


void
dense_layer
(
  hls::stream<float>   flat_to_dense_streams[FILTERS],
  float                prediction [DIGITS]
)
{
  float w_sum = 0.0;
  float dense_array [DENSE_SIZE] = { 0 };
  int index = 0;

  dense_for_filter:
  for (int f = 0; f < FILTERS; ++f)
  {
    dense_for_flat:
    for (int i = 0; i < FLAT_SIZE / FILTERS; ++i)
    {
      float flat_value = flat_to_dense_streams[f].read();

      for (int d = 0; d < DENSE_SIZE; ++d)
        dense_array[d] += dense_weights[index][d] * flat_value;

      ++index;
    }
  }

  dense_bias_for:
  for (int b = 0; b < DENSE_SIZE; ++b)
  {
    dense_array[b] += dense_biases[b];
  }

  soft_max(dense_array, prediction);
}

