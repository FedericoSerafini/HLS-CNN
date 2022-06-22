#pragma once

#include "definitions.h"

void
normalize (
  float img_in  [IMG_ROWS][IMG_COLS], // Input image.
  float img_out [IMG_ROWS][IMG_COLS]  // Normalized image.
);

void
padding(
  float img_in  [IMG_ROWS][IMG_COLS],        // Input image.
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS] // Paded out.
);

#ifndef __SYNTHESIS__
void
print_img(float img[IMG_ROWS][IMG_COLS]);

void
print_pad_img(float img[PAD_IMG_ROWS][PAD_IMG_COLS]);

void
print_features(float features[IMG_ROWS][IMG_COLS][FILTERS]);

void
print_pool_features
(
  float pool_features[POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS]
);
#endif
