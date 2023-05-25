#include "pool.h"

#include <float.h>

#pragma GCC diagnostic ignored "-Wunused-label"

void
max_pool
(
  float feature      [IMG_ROWS][IMG_COLS],
  float pool_feature [POOL_IMG_ROWS][POOL_IMG_COLS]
)
{
  float pool = 0.0;

  for (int r = 0; r < IMG_ROWS; r += POOL_ROWS)
  {
    for(int c = 0; c < IMG_COLS; c += POOL_COLS)
    {
      pool = FLT_MIN;

      for (int pr = 0; pr < POOL_ROWS; ++pr)
        for (int pc = 0; pc < POOL_COLS; ++pc)
        {
          if(feature[r + pr][c + pc] > pool)
            pool = feature[r + pr][c + pc];
        }

      pool_feature[r / POOL_ROWS][c / POOL_COLS] = pool;
    }
  }
}

void
max_pooling_layer
(
  float features      [FILTERS][IMG_ROWS][IMG_COLS],
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
)
{
  for (int f = 0; f < FILTERS; ++f)
  {
    max_pool(features[f], pool_features[f]);
  }
}
