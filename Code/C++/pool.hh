#pragma once

#include "definitions.hh"

void
max_pooling_layer
(
  float features      [FILTERS][IMG_ROWS][IMG_COLS],
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
);
