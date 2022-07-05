#pragma once

#include "../Headers/definitions.h"
#include "../Headers/type_definitions.h"


#include "hls_stream.h"

void
normalization_and_padding(
  float24_t  img_in  [IMG_ROWS][IMG_COLS],
  float24_t  img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
);

#ifndef __SYNTHESIS__

void
print_pad_img
(
  float24_t  img[PAD_IMG_ROWS][PAD_IMG_COLS]
);

void
print_features
(
  hls::stream<float24_t > conv_to_pool_streams[FILTERS]
);

void
print_pool_features
(
  hls::stream<float24_t > pool_to_flat_streams[FILTERS]
);
#endif
