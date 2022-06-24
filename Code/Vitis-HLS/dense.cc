#include "dense.hh"
#include "dense_weights.hh"
#include "activ_fun.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
dense_layer
(
  hls::stream<float>   flat_to_dense_streams[FILTERS], // Flat array.
  float                prediction [DIGITS]
)
{
  float w_sum = 0.0;
  float dense_array [DENSE_SIZE] = { 0 };

  dense_for_f:
  for (int f = 0; f < FILTERS; ++f)
  {
    dense_for_p:
    for (int p = 0; p < FLAT_SIZE / FILTERS; ++p)
    {
      float flat_value = flat_to_dense_streams[f].read();

      for (int d = 0; d < DENSE_SIZE; ++d)
        dense_array[d] += dense_weights[f][d] * flat_value;
    }
  }

  dense_bias_for:
  for (int b = 0; b < DENSE_SIZE; ++b)
  {
    dense_array[b] += dense_biases[b];
  }

  soft_max(dense_array, prediction);
}

