#include "dense.h"
#include "dense_weights.h"
#include "activ_fun.h"

#pragma GCC diagnostic ignored "-Wunused-label"

#include <stdio.h>

void
dense
(
  float flat_array  [FLAT_SIZE],
  float dense_array [DENSE_SIZE]
)
{
  /**********************************************************/
  float deflat_weights [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS][DENSE_SIZE] = { 0 };

  int index = 0;
  for(int i = 0; i < POOL_IMG_ROWS; ++i)
    for(int j = 0; j < POOL_IMG_COLS; ++j)
      for(int f = 0; f < FILTERS; ++f)
      {
        for(int d = 0; d < DENSE_SIZE; ++d)
        {
          deflat_weights[i][j][f][d] = dense_weights_old[index][d];
        }

        ++index;
      }

  index = 0;
  float dense_weights [FLAT_SIZE][DENSE_SIZE] = { 0 };
  for(int f = 0; f < FILTERS; ++f)
    for(int i = 0; i < POOL_IMG_ROWS; ++i)
      for(int j = 0; j < POOL_IMG_COLS; ++j)
      {
        for(int d = 0; d < DENSE_SIZE; ++d)
        {
          dense_weights[index][d] = deflat_weights[i][j][f][d];
        }
        ++index;
      }

  /*******************************************************************/

  float w_sum = 0.0;

  dense_for_d:
  for (uint8_t d = 0U; d < DENSE_SIZE; ++d)
  {
    w_sum = 0.0;

    dense_for_f:
    for (uint16_t f = 0U; f < FLAT_SIZE; ++f)
    {
      w_sum += dense_weights[f][d] * flat_array[f];
    }

    dense_array[d] = w_sum + dense_biases[d];
  }
}

