#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void cnn
(
  float              img_in [IMG_ROWS][IMG_COLS], // Take an image in input.
  hls::stream<float> pred   [DIGITS]              // Get a prediction in output.
);
