#pragma once

#include "../03-Headers/definitions.h"

#include "hls_stream.h"

void
max_pooling_layer
(
  hls::stream<float> conv_to_pool_streams[FILTERS],
  hls::stream<float> pool_to_flat_streams[FILTERS]
);
