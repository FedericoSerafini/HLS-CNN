#include "activ_fun.hh"

float relu (float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}

void soft_max
(
  hls::stream<float> & dense_to_softmax_stream,
  float                prediction[DIGITS]
)
{
  float sum = 0.0;

  float tmp [DIGITS];

  for_exp_sum:
  for (int i = 0; i < DIGITS; ++i)
  {
    tmp[i] = dense_to_softmax_stream.read();
    sum += tmp[i];
  }

  for_prediction:
  for (int j = 0; j < DIGITS; ++j)
  {
    prediction[j] = tmp[j] / sum;
  }
}
