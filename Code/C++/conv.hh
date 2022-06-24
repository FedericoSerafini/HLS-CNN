#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void conv_layer
(
  float              clones [FILTERS][PAD_IMG_ROWS][PAD_IMG_COLS],
  //float features [FILTERS][IMG_ROWS][IMG_COLS].
  hls::stream<float> conv_to_pool_streams [FILTERS]
);
