#include "flat.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
flattening_layer
(
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS],
  float flat_array    [FLAT_SIZE]
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
        flat_array[index] = pool_features[f][r][c];
        ++index;
      }
    }
  }
}
