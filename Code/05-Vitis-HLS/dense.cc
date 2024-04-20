#include "dense.hh"
#include "../03-Headers/dense_weights.h"

#include <cmath>
#include "hls_stream.h"

void dense_layer_soft_max
(
  hls::stream<float>   dense_to_softmax_streams [FILTERS],
  float                prediction               [DIGITS]
)
{
  float sum;
  float exp_sum = 0.0;

  dense_soft_max_for_dense_size:
  for (int d = 0; d < DENSE_SIZE; ++d)
  {
    sum = dense_biases[d];

    dense_soft_max_for_filters:
    for (int f = 0; f < FILTERS; ++f)
    {
      sum += dense_to_softmax_streams[f].read();
    }

    exp_sum += prediction[d] = expf(sum);
  }

  dense_soft_max_for_digits:
  for (int p = 0; p < DIGITS; ++p)
  {
    prediction[p] = prediction[p] / exp_sum;
  }
}

void
dense
(
  hls::stream<float> & flat_to_dense_stream,
  int                  filter,
  hls::stream<float> & dense_to_softmax_stream
)
{
  float flat_value;
  float dense_array[DENSE_SIZE] = { 0 };

  dense_for_flat:
  for (int i = 0; i < FLAT_SIZE / FILTERS; ++i)
  {
    flat_value = flat_to_dense_stream.read();

    for (int d = 0; d < DENSE_SIZE; ++d)
    {
      int index = filter * (FLAT_SIZE / FILTERS) + i;
        dense_array[d] += dense_weights[index][d] * flat_value;
    }
  }

  for (int j = 0; j < DENSE_SIZE; ++j)
  {
    dense_to_softmax_stream.write(dense_array[j]);
  }
}

void
dense_layer
(
  hls::stream<float> flat_to_dense_streams    [FILTERS],
  hls::stream<float> dense_to_softmax_streams [FILTERS]
)
{
  dense(flat_to_dense_streams[0], 0, dense_to_softmax_streams[0]);
  dense(flat_to_dense_streams[1], 1, dense_to_softmax_streams[1]);
  dense(flat_to_dense_streams[2], 2, dense_to_softmax_streams[2]);
  dense(flat_to_dense_streams[3], 3, dense_to_softmax_streams[3]);
}
