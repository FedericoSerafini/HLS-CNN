#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
dense_layer
(
  float flat_array [FLAT_SIZE],
  hls::stream<float> prediction [DIGITS]
);
