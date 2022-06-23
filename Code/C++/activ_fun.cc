#include "activ_fun.hh"

#include <cmath>

#pragma GCC diagnostic ignored "-Wunused-label"

float relu (float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}

void soft_max
(
  hls::stream<float> dense_array [DIGITS],
  hls::stream<float> pred[DIGITS]
)
{
  float sum = 0.0;

  float tmp [DIGITS];

  for_exp_sum:
  for (int i = 0; i < DIGITS; ++i)
  {
    tmp[i] = expf(dense_array[i].read());
    sum += tmp[i];
  }

  for_prediction:
  for (int j = 0; j < DIGITS; ++j)
  {
    pred[j].write(tmp[j] / sum);
  }

}
