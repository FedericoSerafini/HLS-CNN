#pragma once

#include "definitions.h"

void conv
(
  const float   img_in[IMG_ROWS + PAD_ROWS][IMG_COLS + PAD_COLS], // Pad input.
  const uint8_t filter,                                           // Filter id.
  float         img_out[IMG_ROWS][IMG_COLS]                       // Filtered.
);
