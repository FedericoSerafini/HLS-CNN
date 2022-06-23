#pragma once

#include "definitions.hh"

#include "hls_stream.h"

float relu (float x);

void
soft_max
(
  hls::stream<float> dense_array [DIGITS],
  hls::stream<float> pred[DIGITS]
);
