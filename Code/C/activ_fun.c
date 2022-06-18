#include "activ_fun.h"

float relu (const float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}
