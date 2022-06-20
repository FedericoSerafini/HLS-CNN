#include "flat.h"

void
flatten
(
  const float pool_features [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS],
  float       flat_array[FLAT_SIZE]
)
{
  uint16_t index = 0U;

  for(uint8_t r = 0; r < POOL_IMG_ROWS; ++r)
    for(uint8_t c = 0; c < POOL_IMG_COLS; ++c)
      for(uint8_t f = 0; f < FILTERS; ++f)
      {
        flat_array[index] = pool_features[r][c][f];
        ++index;
      }
}
