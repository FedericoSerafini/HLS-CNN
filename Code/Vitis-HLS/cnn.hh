#pragma once

#include "../Headers/definitions.h"
#include "../Headers/type_definitions.h"


void cnn
(
  float24_t img_in [IMG_ROWS][IMG_COLS], // Take an image in input.
  float24_t pred   [DIGITS]              // Get a prediction in output.
);
