#include "conv.h"
#include "definitions.h"
#include "activ_fun.h"
#include "conv_weights.h"

void
conv
(
  const float   pad_img[PAD_IMG_ROWS][PAD_IMG_COLS],
  float         features[IMG_ROWS][IMG_COLS][FILTERS])
{
  float w_sum = 0.0; // Weighted sum.

  for (uint8_t f = 0U; f < FILTERS; ++f)
  {
    for(uint8_t r = 0; r < IMG_ROWS; ++r)
    {
      for(uint8_t c = 0; c < IMG_COLS; ++c)
        {
          w_sum = 0.0;

          for(uint8_t kr = 0; kr < KRN_ROWS; ++kr)
            for(uint8_t kc = 0; kc < KRN_COLS; ++kc)
            {
              w_sum += conv_weights[kr][kc][f] * pad_img[r+kr][c+kc];
            }

          features[r][c][f] = relu(w_sum + conv_biases[f]);
        }
    }
  }
}
