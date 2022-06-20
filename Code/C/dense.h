#pragma once

#include "definitions.h"

void
dense1
(
  const float flat_array   [FLAT_SIZE],
        float dense1_array [DENSE1_SIZE]
);

void
relu_on_dense1
(
  const float dense1_array[DENSE1_SIZE], float dense1_relu[DENSE1_SIZE]
);

void
dense2
(
  const float dense1_array [DENSE1_SIZE],
        float prediction   [DIGITS]
);