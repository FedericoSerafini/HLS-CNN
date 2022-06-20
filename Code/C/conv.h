#pragma once

#include "definitions.h"

void conv
(
  const float   pad_img [PAD_IMG_ROWS][PAD_IMG_COLS], // Pad input.
  const uint8_t filter,                               // Filter id.
  float         img_out [IMG_ROWS][IMG_COLS]          // Filtered.
);
