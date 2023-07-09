#pragma once

#include "../03-Headers/definitions.h"

#include "hls_stream.h"

void
flattening_layer
(
  hls::stream<float>  pool_to_flat_streams[FILTERS],
  hls::stream<float>  flat_to_dense_stream[FILTERS]
);
