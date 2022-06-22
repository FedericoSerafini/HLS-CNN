#include "flat.h"

#pragma GCC diagnostic ignored "-Wunused-label"

void
flatten
(
  float pool_features [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS],
  float flat_array    [FLAT_SIZE]
)
{
  uint16_t index = 0U;

  flat_for_rows:
  for(uint8_t r = 0; r < POOL_IMG_ROWS; ++r)
    flat_for_cols:
    for(uint8_t c = 0; c < POOL_IMG_COLS; ++c)
      flat_for_filters:
      for(uint8_t f = 0; f < FILTERS; ++f)
      {
        flat_array[index] = pool_features[r][c][f];
        ++index;
      }
}
