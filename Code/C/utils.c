#include "definitions.h"
#include "utils.h"

#ifndef __SYNTHESIS__
# include <stdio.h>
#endif

#pragma GCC diagnostic ignored "-Wunused-label"

void
normalize
(
  float img_in  [IMG_ROWS][IMG_COLS],
  float img_out [IMG_ROWS][IMG_COLS]
)
{
  norm_for_rows:
  for (uint8_t r = 0; r < IMG_ROWS; ++r)
  {
    norm_for_cols:
    for(uint8_t c = 0; c < IMG_COLS; ++c)
      img_out[r][c] = img_in[r][c] / 255.0;
  }
}

void
padding
(
  float img_in [IMG_ROWS][IMG_COLS],
  float       img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
)
{
  pad_for_rows:
  for(uint8_t r = 0; r < PAD_IMG_ROWS; ++r)
    pad_for_cols:
    for(uint8_t c = 0; c < PAD_IMG_COLS; ++c)
    {
      if (r == 0 || r == IMG_ROWS + 1)
      {
        // Add pagging.
        img_out[r][c] = 0.0;
      }
      else if (c == 0 || c == IMG_COLS + 1)
      {
        // Add padding.
        img_out[r][c] = 0.0;
      }
      else
      {
        // Copy.
        img_out[r][c] = img_in[r-1][c-1];
      }
    }
  return;
}

#ifndef __SYNTHESIS__

void
print_img(float img[IMG_ROWS][IMG_COLS])
{
  for (uint8_t i = 0; i < IMG_ROWS; ++i)
  {
    for (uint8_t j = 0; j < IMG_COLS; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}

void
print_pad_img(float img[PAD_IMG_ROWS][PAD_IMG_COLS])
{
  for (uint8_t i = 0; i < PAD_IMG_ROWS; ++i)
  {
    for (uint8_t j = 0; j < PAD_IMG_COLS; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}

void
print_features(float features[IMG_ROWS][IMG_COLS][FILTERS])
{
  for (uint8_t f = 0U; f < FILTERS; ++f)
  {
    printf("Feature map %d:\n", f);

    for (uint8_t r = 0; r < IMG_ROWS; ++r)
    {
      for (uint8_t c = 0; c < IMG_COLS; ++c)
      {
        printf("%.0f", features[r][c][f]);
      }
      printf("\n");
    }
  }
}

void
print_pool_features
(
  float pool_features[POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS]
)
{
  for (uint8_t f = 0U; f < FILTERS; ++f)
  {
    printf("Pool feature map %d:\n", f);
    for (uint8_t r = 0; r < POOL_IMG_ROWS; ++r)
    {
      for (uint8_t c = 0; c < POOL_IMG_COLS; ++c)
      {
        printf("%.0f", pool_features[r][c][f]);
      }
      printf("\n");
    }
  }
}

#endif
