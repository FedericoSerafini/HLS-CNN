#include "flat.hh"

void
flattening
(
  hls::stream<float> &  pool_to_flat_stream,
  hls::stream<float> &  flat_to_dense_stream
)
{
  flat_for_rows:
  for(int r = 0; r < POOL_IMG_ROWS; ++r)
  {
    flat_for_cols:
    for(int c = 0; c < POOL_IMG_COLS; ++c)
    {
      flat_to_dense_stream.write(pool_to_flat_stream.read());
    }
  }
}

void
flattening_layer
(
  hls::stream<float> pool_to_flat_streams[FILTERS],
  hls::stream<float> flat_to_dense_streams[FILTERS]
)
{
  flattening(pool_to_flat_streams[0], flat_to_dense_streams[0]);
  flattening(pool_to_flat_streams[1], flat_to_dense_streams[1]);
  flattening(pool_to_flat_streams[2], flat_to_dense_streams[2]);
  flattening(pool_to_flat_streams[3], flat_to_dense_streams[3]);
}
