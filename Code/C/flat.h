#pragma once

#include "definitions.h"

void
flattening_layer
(
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS],
  float flat_array    [FLAT_SIZE]
);
