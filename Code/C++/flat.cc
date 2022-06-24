#include "flat.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
flattening_layer
(
  hls::stream<float> & stream_pool_to_flat,
  hls::stream<float> & stream_flat_to_dense
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
        stream_flat_to_dense.write(stream_pool_to_flat.read());
        ++index;
      }
    }
  }
}
