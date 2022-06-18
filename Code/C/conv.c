#include "conv.h"
#include "definitions.h"
#include "activ_fun.h"
#include "weight_conv.h"

void
conv
(
  const float   img_in[IMG_ROWS + PAD_ROWS][IMG_COLS + PAD_COLS],
  const uint8_t filter,
  float         img_out[IMG_ROWS][IMG_COLS])
{
  float w_sum = 0; // Weighted sum.

  for(uint8_t i = 0; i < IMG_ROWS; ++i)   // Stride instead of ++ ?
    for(uint8_t j = 0; j < IMG_COLS; ++j) // Stride instead of ++ ?
    {
      w_sum = 0;

      for(uint8_t ki = 0; ki < KRN_ROWS; ++ki)
        for(uint8_t kj = 0; kj < KRN_COLS; ++kj)
        {
          w_sum += krn_filters[filter][ki][kj] * img_in[i+ki][j+kj];
        }

     img_out[i][j] = relu(w_sum + krn_biases[filter]);
    }
}
