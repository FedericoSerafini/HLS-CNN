#include "flat.h"

void
flatten
(
  const float pool_image[FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS],
  float       img_out[FLAT_SIZE]
)
{
  uint16_t index = 0;

  flat_for_filters:
  for(uint8_t f = 0; f < FILTERS; ++f)
	flat_for_rows:
    for(uint8_t i = 0; i < POOL_IMG_ROWS; ++i)
      flat_for_cols:
      for(uint8_t j = 0; j < POOL_IMG_COLS; ++j)
      {
        img_out[index] = pool_image[f][i][j];
        ++index;
      }
}
