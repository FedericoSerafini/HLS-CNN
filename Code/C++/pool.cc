#include "pool.hh"

#include <cfloat>

#pragma GCC diagnostic ignored "-Wunused-label"

void
max_pooling_layer
(
  hls::stream<float> & stream_conv_to_pool,
  hls::stream<float> & stream_pool_to_flat
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
        pool = FLT_MIN;

        pool_for_pr:
        for (int pr = 0; pr < POOL_ROWS; ++pr)
          pool_for_pc:
          for (int pc = 0; pc < POOL_COLS; ++pc)
          {
            //float value = features[f][r + pr][c + pc];
            float value = stream_conv_to_pool.read();
            if(value > pool)
              pool = value;
          }

        stream_pool_to_flat.write(pool);
      }
    }
  }
}
