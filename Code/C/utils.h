#pragma once

#include "definitions.h"

void
normalize (
  const float img_in  [IMG_ROWS][IMG_COLS], // Input image.
  float       img_out [IMG_ROWS][IMG_COLS]  // Normalized image.
);

void
padding(
  const float img_in [IMG_ROWS][IMG_COLS],         // Input image.
  float       img_out [IMG_ROWS + 2][IMG_COLS + 2] // Padded image.
);

void
print_img(const float img[IMG_ROWS][IMG_COLS]);

void
print_pad_img(const float img[IMG_ROWS + 2][IMG_COLS + 2]);
