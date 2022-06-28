#include "dense.hh"
#include "activ_fun.hh"
#include "../Headers/dense_weights.h"

#include "hls_stream.h"
#include <cmath>

void
dense_layer
(
  hls::stream<float>     flat_to_dense_streams   [FILTERS],
  hls::stream<float>   & dense_to_softmax_stream
)
{
  float w_sum = 0.0;
  float dense_array [DENSE_SIZE] = { 0 };
  float flat_value;


  dense_for_flat:
  for (int i = 0; i < FLAT_SIZE / FILTERS; ++i)
  {
    dense_for_filter:
    for (int f = 0; f < FILTERS; ++f)
    {
      flat_value = flat_to_dense_streams[f].read();

      for (int d = 0; d < DENSE_SIZE; ++d)
        dense_array[d] += dense_weights[f * (FLAT_SIZE / FILTERS) + i][d] * flat_value;
    }
  }

  dense_bias_for:
  for (int b = 0; b < DENSE_SIZE; ++b)
  {
    dense_to_softmax_stream.write(expf(dense_array[b] + dense_biases[b]));
  }

}

