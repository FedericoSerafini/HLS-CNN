#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
flattening_layer
(
  // pool_features [FILTERS][PAD_IMG_COLS][PAD_IMG_ROWS].
  hls::stream<float> & stream_pool_to_flat,
  // flat_array [FLAT_SIZE].
  hls::stream<float> & stream_flat_to_dense
);
