#pragma once

#include "../Headers/definitions.h"
#include "../Headers/type_definitions.h"


#include "hls_stream.h"


void dense_layer_soft_max
(
  hls::stream<float24_t>   dense_to_softmax_streams [FILTERS],
  float24_t                prediction               [DIGITS]
);

void
dense_layer
(
  hls::stream<float24_t> flat_to_dense_streams[FILTERS],
  hls::stream<float24_t> dense_to_softmax_stream[FILTERS]
);
