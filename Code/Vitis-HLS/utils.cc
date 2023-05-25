#include "../Headers/definitions.h"
#include "utils.hh"

#ifndef __SYNTHESIS__
# include <cstdio>
#endif

void
normalization_and_padding
(
  float img_in  [IMG_ROWS][IMG_COLS],
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
)
{
  pad_for_rows:
  for(int r = 0; r < PAD_IMG_ROWS; ++r)
    pad_for_cols:
    for(int c = 0; c < PAD_IMG_COLS; ++c)
    {
      if (r == 0 || r == IMG_ROWS + 1)
      {
        // Add padding.
        img_out[r][c] = 0.0;
      }
      else if (c == 0 || c == IMG_COLS + 1)
      {
        // Add padding.
        img_out[r][c] = 0.0;
      }
      else
      {
        // Normalize.
        img_out[r][c] = img_in[r-1][c-1] / 255.0;
      }
    }
}

#ifndef __SYNTHESIS__

void
print_pad_img(float img[PAD_IMG_ROWS][PAD_IMG_COLS])
{
  for (int i = 0; i < PAD_IMG_ROWS; ++i)
  {
    for (int j = 0; j < PAD_IMG_COLS; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}

void
print_features
(
  hls::stream<float> conv_to_pool_streams[FILTERS]
)
{
  for (int f = 0; f < FILTERS; ++f)
  {
    printf("Feature map %d:\n", f);

    for (int r = 0; r < IMG_ROWS; ++r)
    {
      for (int c = 0; c < IMG_COLS; ++c)
      {
        printf("%.0f", conv_to_pool_streams[f].read());
      }
      printf("\n");
    }
  }
}

void
print_pool_features
(
  hls::stream<float> pool_to_flat_streams[FILTERS]
)
{
  for (int f = 0; f < FILTERS; ++f)
  {
    printf("Pool feature map %d:\n", f);

    for (int r = 0; r < POOL_IMG_ROWS; ++r)
    {
      for (int c = 0; c < POOL_IMG_COLS; ++c)
      {
        printf("%.0f", pool_to_flat_streams[f].read());
      }
      printf("\n");
    }
  }
}

#endif
