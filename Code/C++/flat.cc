#include "flat.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
flattening_layer
(
  hls::stream<float>   pool_to_flat_streams[FILTERS],
  hls::stream<float> & flat_to_dense_stream
)
{
  int index = 0;

  flat_for_filters:
  for(int f = 0; f < FILTERS; ++f)
  {
    flat_for_rows:
    for(int r = 0; r < POOL_IMG_ROWS; ++r)
    {
      flat_for_cols:
      for(int c = 0; c < POOL_IMG_COLS; ++c)
      {
        flat_to_dense_stream.write(pool_to_flat_streams[f].read());
        ++index;
      }
    }
  }
}
