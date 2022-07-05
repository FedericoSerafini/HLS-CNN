#pragma once

#include "../Headers/definitions.h"
#include "../Headers/type_definitions.h"


#include "hls_stream.h"

void
flattening_layer
(
  hls::stream<float24_t>  pool_to_flat_streams[FILTERS],
  hls::stream<float24_t>  flat_to_dense_stream[FILTERS]
);
