#pragma once

#include "../Headers/definitions.h"
#include "../Headers/type_definitions.h"


#include "hls_stream.h"

void
max_pooling_layer
(
  hls::stream<float24_t > conv_to_pool_streams[FILTERS],
  hls::stream<float24_t > pool_to_flat_streams[FILTERS]
);
