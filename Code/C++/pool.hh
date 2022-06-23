#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
max_pooling_layer
(
  hls::stream<float> features      [FILTERS][IMG_ROWS][IMG_COLS],
  hls::stream<float> pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
);
