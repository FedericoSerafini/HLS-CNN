#pragma once

#include "definitions.h"
#include "weights.h"

#include <stdint.h>

void cnn
(
  const float img_in[IMG_ROWS][IMG_COLS], // Take an image in input.
  float       pred[10]                    // Get a prediction in output.
);
