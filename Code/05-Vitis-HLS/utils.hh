#pragma once

#include "../03-Headers/definitions.h"

#include "hls_stream.h"

void
normalization_and_padding(
  float img_in  [IMG_ROWS][IMG_COLS],
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
);

#ifndef __SYNTHESIS__

void
print_pad_img
(
  float img[PAD_IMG_ROWS][PAD_IMG_COLS]
);

void
print_features
(
  hls::stream<float> conv_to_pool_streams[FILTERS]
);

void
print_pool_features
(
  hls::stream<float> pool_to_flat_streams[FILTERS]
);
#endif
