#include "pool.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
max_pooling_layer
(
  float features      [FILTERS][IMG_ROWS][IMG_COLS],
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
)
{
  pool_for_filters:
  for (int f = 0; f < FILTERS; ++f)
  {
    float pool = 0.0;

    pool_for_rows:
    for (int r = 0; r < IMG_ROWS; r += POOL_ROWS)
    {
      pool_for_cols:
      for(int c = 0; c < IMG_COLS; c += POOL_COLS)
      {
        pool = features[f][r][c];

        pool_for_pr:
        for (int pr = 0; pr < POOL_ROWS; ++pr)
          pool_for_pc:
          for (int pc = 0; pc < POOL_COLS; ++pc)
          {
            float value = features[f][r + pr][c + pc];
            if(value > pool)
              pool = value;
          }

        pool_features[f][r / POOL_ROWS][c / POOL_COLS] = pool;
      }
    }
  }
}
