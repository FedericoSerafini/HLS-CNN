#pragma once

#include "definitions.h"

const float conv1_krn_filters [KRN_FILTERS][KRN_ROWS][KRN_COLS]
  = {
      { // 1 filter.

        // 3 rows.
        {0.11, 0.11, 0.11}, // 3 cols.
        {0.11, 0.11, 0.11},
        {0.11, 0.11, 0.11}
      }
    };

const float conv1_krn_biases [KRN_FILTERS] = { 0 };