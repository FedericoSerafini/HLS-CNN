#pragma once

#include "definitions.h"

void
max_pooling
(
  float features      [IMG_ROWS][IMG_COLS][FILTERS],
  float pool_features [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS]
);
