#pragma once

#include "definitions.h"

void
flatten
(
  const float pool_features [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS],
  float       flat_array    [FLAT_SIZE]
);
