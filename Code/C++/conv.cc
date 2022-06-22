#include "conv.hh"
#include "definitions.hh"
#include "activ_fun.hh"
#include "conv_weights.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
apply_filter
(
  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  int   filter,
  float feature [IMG_ROWS][IMG_COLS]
)
{
  float w_sum = 0.0; // Weighted sum.

  filter_for_rows:
  for(int r = 0; r < IMG_ROWS; ++r)
  {
    filter_for_cols:
    for(int c = 0; c < IMG_COLS; ++c)
      {
        w_sum = 0.0;

        krn_for_rows:
        for(int kr = 0; kr < KRN_ROWS; ++kr)
        {
          krn_for_cols:
          for(int kc = 0; kc < KRN_COLS; ++kc)
          {
            w_sum += conv_weights[filter][kr][kc] * pad_img[r+kr][c+kc];
          }
        }

        feature[r][c] = relu(w_sum + conv_biases[filter]);
      }
  }
}

void
conv_layer
(
  float pad_img  [PAD_IMG_ROWS][PAD_IMG_COLS],
  float features [FILTERS][IMG_ROWS][IMG_COLS]
)
{
  conv_for:
  for (int f = 0; f < FILTERS; ++f)
  {
    apply_filter(pad_img, f, features[f]);
  }
}
