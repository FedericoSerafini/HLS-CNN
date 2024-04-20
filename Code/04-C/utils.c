#include "definitions.h"
#include "utils.h"


#include <stdio.h>

void
normalization_and_padding
(
  float img_in  [IMG_ROWS][IMG_COLS],
  float img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
)
{
  for(int r = 0; r < IMG_ROWS; ++r)
    for(int c = 0; c < IMG_COLS; ++c)
    {
      {
        // Normalize.
        img_out[r + PAD_ROWS / 2][c + PAD_ROWS / 2] = img_in[r][c] / 255.0;
      }
    }
}

#ifndef __SYNTHESIS__

void
print_img(float img[IMG_ROWS][IMG_COLS])
{
  for (int i = 0; i < IMG_ROWS; ++i)
  {
    for (int j = 0; j < IMG_COLS; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}

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
print_features(float features [FILTERS][IMG_ROWS][IMG_COLS])
{
  for (int f = 0; f < FILTERS; ++f)
  {
    printf("Feature map %d:\n", f);

    for (int r = 0; r < IMG_ROWS; ++r)
    {
      for (int c = 0; c < IMG_COLS; ++c)
      {
        printf("%.0f", features[f][r][c]);
      }
      printf("\n");
    }
  }
}

void
print_pool_features
(
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS]
)
{
  for (int f = 0; f < FILTERS; ++f)
  {
    printf("Pool feature map %d:\n", f);
    for (int r = 0; r < POOL_IMG_ROWS; ++r)
    {
      for (int c = 0; c < POOL_IMG_COLS; ++c)
      {
        printf("%.0f", pool_features[f][r][c]);
      }
      printf("\n");
    }
  }
}

#endif
