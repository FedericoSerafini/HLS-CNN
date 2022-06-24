#pragma once

#include "definitions.hh"

void conv_layer
(
  float pad_img  [PAD_IMG_ROWS][PAD_IMG_COLS], // Pad input.
  float features [FILTERS][IMG_ROWS][IMG_COLS] // Filtered.
);
