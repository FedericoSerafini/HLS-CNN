#pragma once

#include "definitions.h"

void conv
(
  const float   pad_img  [PAD_IMG_ROWS][PAD_IMG_COLS], // Pad input.
  float         features [IMG_ROWS][IMG_COLS][FILTERS]  // Filtered.
);
