#pragma once

#include "definitions.hh"

float relu (float x);

void
soft_max
(
  float dense_array [DIGITS],
  float pred        [DIGITS]
);
