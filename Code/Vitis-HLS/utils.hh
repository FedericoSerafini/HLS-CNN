#pragma once

#include "../Headers/definitions.h"

#include "hls_stream.h"

void
normalization_and_padding(
  float img_in  [IMG_ROWS][IMG_COLS],        // Input image.
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS] // Paded out.
);

void
clone
(
  float img_in  [PAD_IMG_ROWS][PAD_IMG_COLS],
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
);

#ifndef __SYNTHESIS__

void
print_pad_img(float img[PAD_IMG_ROWS][PAD_IMG_COLS]);

void
print_features(float features [FILTERS][IMG_ROWS][IMG_COLS]);

void
print_pool_features
(
  hls::stream<float> pool_to_flat_streams[FILTERS]
);
#endif
