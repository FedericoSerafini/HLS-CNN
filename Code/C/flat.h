#pragma once

#include "definitions.h"

void
flatten
(
  const float
  pool_images[KRN_FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS],
  float img_out[FLAT_SIZE]
);
