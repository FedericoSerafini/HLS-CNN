#pragma once

#include "definitions.h"

void
normalize (
  const float img_in  [IMG_ROWS][IMG_COLS], // Input image.
  float       img_out [IMG_ROWS][IMG_COLS]  // Normalized image.
);

void
padding(
  const float img_in [IMG_ROWS][IMG_COLS],                       // Input image.
  float       img_out [PAD_IMG_ROWS][PAD_IMG_COLS] // Paded out.
);

#ifndef __SYNTHESIS__
void
print_img(const float img[IMG_ROWS][IMG_COLS]);

void
print_pad_img(const float img[PAD_IMG_ROWS][PAD_IMG_COLS]);

void
print_pool_img(const float img[POOL_IMG_ROWS][POOL_IMG_COLS]);
#endif
