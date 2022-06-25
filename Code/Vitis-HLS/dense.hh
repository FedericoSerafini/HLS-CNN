#pragma once

#include "../Headers/definitions.h"

#include "hls_stream.h"

void
dense_layer
(
  hls::stream<float>   flat_to_dense_streams[FILTERS],
  hls::stream<float> & dense_to_softmax_stream
);