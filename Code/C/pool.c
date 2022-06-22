#include "pool.h"

#include <float.h>

#pragma GCC diagnostic ignored "-Wunused-label"

void
max_pooling
(
  float features      [IMG_ROWS][IMG_COLS][FILTERS],
  float pool_features [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS]
)
{
  float pool = 0.0;

  pool_for_filters:
  for (uint8_t f = 0U; f < FILTERS; ++f)
  {
    pool_for_rows:
    for (uint8_t r = 0; r < IMG_ROWS; r += POOL_ROWS)
    {
      pool_for_cols:
      for(uint8_t c = 0; c < IMG_COLS; c += POOL_COLS)
      {
        pool = FLT_MIN;

        pool_for_prows:
        for (uint8_t pr = 0U; pr < POOL_ROWS; ++pr)
          pool_for_pcols:
          for (uint8_t pc = 0; pc < POOL_COLS; ++pc)
          {
            if(features[r + pr][c + pc][f] > pool)
              pool = features[r + pr][c + pc][f];
          }

        pool_features[r / POOL_ROWS][c / POOL_COLS][f] = pool;
      }
    }
  }
}
