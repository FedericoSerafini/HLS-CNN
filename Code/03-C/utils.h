#pragma once

#include "definitions.h"

void
normalization_and_padding(
  float img_in  [IMG_ROWS][IMG_COLS],        // Input image.
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS] // Paded out.
);

#ifndef __SYNTHESIS__
void
print_img(float img[IMG_ROWS][IMG_COLS]);

void
print_pad_img(float img[PAD_IMG_ROWS][PAD_IMG_COLS]);

void
print_features(float features [FILTERS][IMG_ROWS][IMG_COLS]);

void
print_pool_features
(
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
);
#endif
