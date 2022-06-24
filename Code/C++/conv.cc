#include "conv.hh"
#include "definitions.hh"
#include "activ_fun.hh"
#include "conv_weights.hh"

#pragma GCC diagnostic ignored "-Wunused-label"

void
conv_layer
(
  float                pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  //float features [FILTERS][IMG_ROWS][IMG_COLS]
  hls::stream<float> & stream_conv_to_pool
)
{
  float w_sum = 0.0; // Weighted sum.

  conv_for:
  for (int f = 0; f < FILTERS; ++f)
  {
    filter_for_rows:
    for(int r = 0; r < IMG_ROWS; r += POOL_ROWS)
    {
      filter_for_cols:
      for(int c = 0; c < IMG_COLS; c += POOL_COLS)
      {
        windo_for_rows:
        for (int wr = 0; wr < KRN_ROWS -1; ++wr)
          window_for_cols:
          for (int wc = 0; wc < KRN_COLS -1; ++wc)
          {
            w_sum = 0.0;

            krn_for_rows:
            for(int kr = 0; kr < KRN_ROWS; ++kr)
            {
              krn_for_cols:
              for(int kc = 0; kc < KRN_COLS; ++kc)
              {
                float w     = conv_weights[f][kr][kc];
                float pixel = pad_img[r+wr+kr][c+wc+kc];
                w_sum +=  w * pixel;
              }
            }

            #if 0
              features[f][r][c] = relu(w_sum + conv_biases[f]);
            #endif
            stream_conv_to_pool.write(relu(w_sum + conv_biases[f]));
          }
      }
    }
  }
}
