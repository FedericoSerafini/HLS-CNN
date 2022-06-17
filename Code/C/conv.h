#pragma once

#include "definitions.h"

void conv
(
  const float img_in[IMG_ROWS + 2][IMG_COLS + 2],
  const float kernel[KERNEL_ROWS][KERNEL_COLS],
  float       img_out[IMG_ROWS][IMG_COLS]
);
