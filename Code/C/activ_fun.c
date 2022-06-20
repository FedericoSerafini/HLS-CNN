#include "activ_fun.h"

#include <math.h>

float relu (const float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}

void soft_max(const float dense2_array [DIGITS], float pred[DIGITS])
{
  float sum = 0.0;

  soft_for_sum:
  for (uint8_t i = 0; i < DIGITS; ++i)
  {
    sum += expf(dense2_array[i]);
  }

  soft_for_compute:
  for (uint8_t j = 0; j < DIGITS; ++j)
  {
    pred[j] = expf(dense2_array[j]) / sum;
  }

}
