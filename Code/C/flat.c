#include "flat.h"

void
flatten
(
  const float pool_images[KRN_FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS],
  float       img_out[FLAT_SIZE]
)
{
  uint16_t index = 0;

  for(uint8_t f = 0; f < KRN_FILTERS; ++f)
    for(uint8_t i = 0; i < POOL_IMG_ROWS; ++i)
      for(uint8_t j = 0; j < POOL_IMG_COLS; ++j)
      {
        img_out[index] = pool_images[f][i][j];
        ++ index;
      }
}
