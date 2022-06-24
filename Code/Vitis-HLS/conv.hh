#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
convolution
(
  float                pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  int                  filter,
  hls::stream<float> & conv_to_pool_stream
);

void convolutional_layer
(
  float                pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  float                pad_img1 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float                pad_img2 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float                pad_img3 [PAD_IMG_ROWS][PAD_IMG_COLS],
  //float features [FILTERS][IMG_ROWS][IMG_COLS]
  hls::stream<float> conv_to_pool_streams [FILTERS]
);
