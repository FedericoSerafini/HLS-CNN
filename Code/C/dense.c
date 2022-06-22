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
  float dense_weights [FLAT_SIZE][DENSE_SIZE] = { 0 };

  for(int i = 0; i < POOL_IMG_ROWS; ++i)
    for(int j = 0; j < POOL_IMG_COLS; ++j)
      for(int f = 0; f < FILTERS; ++f)
        for(int d = 0; d < DENSE_SIZE; ++d)
        {
          int index_old = (i * POOL_IMG_COLS * FILTERS) + (j * FILTERS) + f;
          int index_new = (f * POOL_IMG_ROWS * POOL_IMG_COLS) + (i * FILTERS) + j;

          dense_weights[index_new][d] = dense_weights_old[index_old][d];
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

