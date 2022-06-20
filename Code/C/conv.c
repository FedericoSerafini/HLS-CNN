#include "conv.h"
#include "definitions.h"
#include "activ_fun.h"
#include "conv_weights.h"

void
conv
(
  const float   pad_img[PAD_IMG_ROWS][PAD_IMG_COLS],
  const uint8_t filter,
  float         img_out[IMG_ROWS][IMG_COLS])
{
  float w_sum = 0; // Weighted sum.

  conv_for_rows:
  for(uint8_t i = 0; i < IMG_ROWS; ++i)
	conv_for_cols:
    for(uint8_t j = 0; j < IMG_COLS; ++j)
    {
      w_sum = 0;

      for(uint8_t ki = 0; ki < KRN_ROWS; ++ki)
        for(uint8_t kj = 0; kj < KRN_COLS; ++kj)
        {
          w_sum += conv_weights[filter][ki][kj] * pad_img[i+ki][j+kj];
        }

     img_out[i][j] = relu(w_sum + conv_biases[filter]);
    }
}
