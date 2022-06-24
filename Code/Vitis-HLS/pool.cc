#include "pool.hh"

#include <cfloat>

void
max_pooling
(
  hls::stream<float> & conv_to_pool_stream,
  hls::stream<float> & pool_to_flat_stream
)
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
          float value = conv_to_pool_stream.read();
          if(value > pool)
            pool = value;
        }

      pool_to_flat_stream.write(pool);
    }
  }
}

void
max_pooling_layer
(
  hls::stream<float> conv_to_pool_streams[FILTERS],
  hls::stream<float> pool_to_flat_streams[FILTERS]
)
{
    max_pooling(conv_to_pool_streams[0], pool_to_flat_streams[0]);
    max_pooling(conv_to_pool_streams[1], pool_to_flat_streams[1]);
    max_pooling(conv_to_pool_streams[2], pool_to_flat_streams[2]);
    max_pooling(conv_to_pool_streams[3], pool_to_flat_streams[3]);
}
