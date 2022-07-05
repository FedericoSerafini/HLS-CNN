#pragma once

#include "../Headers/definitions.h"
#include "../Headers/type_definitions.h"


#include "hls_stream.h"

void
convolution
(
  float24_t                pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  int                  filter,
  hls::stream<float24_t> & conv_to_pool_stream
);

void convolutional_layer
(
  float24_t                pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img1 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img2 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img3 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img4 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img5 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img6 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float24_t                pad_img7 [PAD_IMG_ROWS][PAD_IMG_COLS],
  hls::stream<float24_t> conv_to_pool_streams [FILTERS]
);
