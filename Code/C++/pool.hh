#pragma once

#include "definitions.hh"

#include "hls_stream.h"

void
max_pooling_layer
(
  hls::stream<float> & stream_conv_to_pool,
  hls::stream<float> & stream_pool_to_flat
);
