#include "activ_fun.h"

#include <math.h>

float relu (const float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}

void soft_max(const float img_in [DIGITS], float pred[DIGITS])
{
  float sum = 0.0;

  for (uint8_t i = 0; i < DIGITS; ++i)
  {
    sum += expf(img_in[i]);
  }

  for (uint8_t i = 0; i < DIGITS; ++i)
  {
    pred[i] = expf(img_in[i]) / sum;
  }

}
