#pragma once

#include "definitions.h"

void
max_pooling
(
  const float img_in[IMG_ROWS][IMG_COLS],
  float       img_out[POOL_IMG_ROWS][POOL_IMG_COLS]
);
