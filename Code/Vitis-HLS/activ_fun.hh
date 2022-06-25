#pragma once

#include "../Headers/definitions.h"

#include "hls_stream.h"

float relu (float x);

void
soft_max
(
  hls::stream<float> & dense_to_softmax,
  float                prediction[DIGITS]
);
