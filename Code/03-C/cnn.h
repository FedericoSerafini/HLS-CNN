#pragma once

#include "definitions.h"

void cnn
(
  float img_in [IMG_ROWS][IMG_COLS], // Take an image in input.
  float pred   [DIGITS]              // Get a prediction in output.
);
