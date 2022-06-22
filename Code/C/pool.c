#include "pool.h"

#include <float.h>

#pragma GCC diagnostic ignored "-Wunused-label"

void
max_pooling
(
  float features      [FILTERS][IMG_ROWS][IMG_COLS],
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
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
            if(features[f][r + pr][c + pc] > pool)
              pool = features[f][r + pr][c + pc];
          }

        pool_features[f][r / POOL_ROWS][c / POOL_COLS] = pool;
      }
    }
  }
}
