#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
flattening_layer
(
  hls::stream<float> pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS],
  float              flat_array    [FLAT_SIZE]
);
