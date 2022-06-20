#pragma once

#include "definitions.h"

void
max_pooling
(
  const float feature[IMG_ROWS][IMG_COLS],
  float       pool_feature[POOL_IMG_ROWS][POOL_IMG_COLS]
);
