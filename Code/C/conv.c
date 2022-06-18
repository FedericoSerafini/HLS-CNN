#include "conv.h"
#include "definitions.h"
#include "activ_fun.h"
#include "weight_conv.h"

void
conv
(
  const float   img_in[IMG_ROWS + 2][IMG_COLS + 2],
  const uint8_t filter,
  float         img_out[IMG_ROWS][IMG_COLS])
{
  float w_sum = 0; // Weighted sum.

  for(int i = 0; i < IMG_ROWS; ++i)
    for(int j = 0; j < IMG_COLS; ++j)
    {
      w_sum = 0;

      for(int ki = 0; ki < KRN_ROWS; ++ki)
        for(int kj = 0; kj < KRN_COLS; ++kj)
        {
          w_sum += conv1_krn_filters[filter][ki][kj] * img_in[i+ki][j+kj];
        }

     img_out[i][j] = relu(w_sum) + conv1_krn_biases[filter];
    }
}
