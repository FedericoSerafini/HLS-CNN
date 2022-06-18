#pragma once

#include "definitions.h"

void conv
(
  const float   img_in[IMG_ROWS + 2][IMG_COLS + 2],
  const uint8_t filter,
  float         img_out[IMG_ROWS][IMG_COLS]
);
