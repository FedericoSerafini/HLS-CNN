#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
dense_layer
(
  // flat_array [FLAT_SIZE].
  hls::stream<float> & stream_flat_to_dense,
  float                prediction [DIGITS]
);
