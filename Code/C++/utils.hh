#pragma once

#include "definitions.hh"

#include "hls_stream.h"

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

void
clone
(
  float img_in  [PAD_IMG_ROWS][PAD_IMG_COLS],
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
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
  hls::stream<float> pool_to_flat_streams[FILTERS]
);
#endif
