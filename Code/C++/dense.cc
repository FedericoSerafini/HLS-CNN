#include "dense.hh"
#include "dense_weights.hh"
#include "activ_fun.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
dense_layer
(
  hls::stream<float> & stream_flat_to_dense, // Flat array.
  float                prediction [DIGITS]
)
{
  float w_sum = 0.0;
  float dense_array [DENSE_SIZE] = { 0 };

  dense_for_f:
  for (int f = 0; f < FLAT_SIZE; ++f)
  {
    float flat_value = stream_flat_to_dense.read();

    dense_for_d:
    for (int d = 0; d < DENSE_SIZE; ++d)
    {
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

