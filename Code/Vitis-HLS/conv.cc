#include "conv.hh"
#include "../Headers/conv_weights.h"
#include "../Headers/definitions.h"

float relu (float x)
{
  if(x > 0.0)
    return x;
  else
    return 0.0;
}

void
convolution
(
  float                pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  int                  filter,
  hls::stream<float> & conv_to_pool_stream
)
{
  float w_sum = 0.0; // Weighted sum.

  conv_for_rows:
  for(int r = 0; r < IMG_ROWS; r += POOL_ROWS)
  {
    conv_for_cols:
    for(int c = 0; c < IMG_COLS; c += POOL_COLS)
    {
      win_for_rows:
      for (int wr = 0; wr < KRN_ROWS -1; ++wr)
        win_for_cols:
        for (int wc = 0; wc < KRN_COLS -1; ++wc)
        {
          w_sum = 0.0;

          krn_for_rows:
          for(int kr = 0; kr < KRN_ROWS; ++kr)
          {
            krn_for_cols:
            for(int kc = 0; kc < KRN_COLS; ++kc)
            {
              float w     = conv_weights[filter][kr][kc];
              float pixel = pad_img[r+wr+kr][c+wc+kc];
              w_sum +=  w * pixel;
            }
          }

          conv_to_pool_stream.write(relu(w_sum + conv_biases[filter]));
        }
    }
  }
}

void
convolutional_layer
(
  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img1 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img2 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img3 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img4 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img5 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img6 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img7 [PAD_IMG_ROWS][PAD_IMG_COLS],
  hls::stream<float> conv_to_pool_streams [FILTERS]
)
{
  convolution(pad_img,  0, conv_to_pool_streams[0]);
  convolution(pad_img1, 1, conv_to_pool_streams[1]);
  convolution(pad_img2, 2, conv_to_pool_streams[2]);
  convolution(pad_img3, 3, conv_to_pool_streams[3]);
  convolution(pad_img4, 4, conv_to_pool_streams[4]);
  convolution(pad_img5, 5, conv_to_pool_streams[5]);
  convolution(pad_img6, 6, conv_to_pool_streams[6]);
  convolution(pad_img7, 7, conv_to_pool_streams[7]);
}
