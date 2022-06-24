#include "activ_fun.h"

#include <math.h>

float relu (float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}

void soft_max(float dense_array [DIGITS], float pred[DIGITS])
{
  float sum = 0.0;

  for (int i = 0; i < DIGITS; ++i)
  {
    sum += expf(dense_array[i]);
  }

  for (int j = 0; j < DIGITS; ++j)
  {
    pred[j] = expf(dense_array[j]) / sum;
  }

}
