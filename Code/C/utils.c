#include "definitions.h"
#include "utils.h"

#ifndef __SYNTHESIS__
# include <stdio.h>
#endif

void
normalize
(
  const float img_in  [IMG_ROWS][IMG_COLS],
  float       img_out [IMG_ROWS][IMG_COLS]
)
{
  #ifdef __SYNTHESYS__
  norm_for_rows:
  #endif
  for (uint8_t i = 0; i < IMG_ROWS; ++i)
  {
    #ifdef __SYNTHESYS__
    norm_for_cols:
    #endif
    for(uint8_t j = 0; j < IMG_COLS; ++j)
      img_out[i][j] = img_in[i][j] / 255.0;
  }
}

void
padding
(
  const float img_in [IMG_ROWS][IMG_COLS],
  float       img_out [PAD_IMG_ROWS][PAD_IMG_COLS]
)
{
  #ifdef __SYNTHESYS__
  norm_pad_rows:
  #endif
  for(uint8_t i = 0; i < PAD_IMG_ROWS; ++i)
    #ifdef __SYNTHESYS__
	  norm_pad_cols:
    #endif
    for(uint8_t j = 0; j < PAD_IMG_COLS; ++j)
    {
      if (i == 0 || i == IMG_ROWS + 1)
      {
        // Add pagging.
        img_out[i][j] = 0.0;
      }
      else if (j == 0 || j == IMG_COLS + 1)
      {
        // Add padding.
        img_out[i][j] = 0.0;
      }
      else
      {
        // Copy.
        img_out[i][j] = img_in[i-1][j-1];
      }
    }
  return;
}

#ifndef __SYNTHESIS__
void
print_img(const float img[IMG_ROWS][IMG_COLS])
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
print_pad_img(const float img[PAD_IMG_ROWS][PAD_IMG_COLS])
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
print_features(const float features[IMG_ROWS][IMG_COLS][FILTERS])
{
  for (uint8_t f = 0U; f < FILTERS; ++f)
  {
    printf("Feature map %d:\n", f);

    for (uint8_t r = 0; r < IMG_ROWS; ++r)
    {
      for (uint8_t c = 0; c < IMG_COLS; ++c)
      {
        printf("%.0f ", features[r][c][f]);
      }
      printf("\n");
    }
  }
}

void
print_pool_features
(
  const float pool_features[POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS]
)
{
  for (uint8_t f = 0U; f < FILTERS; ++f)
  {
    printf("Pool feature map %d:\n", f);
    for (uint8_t r = 0; r < POOL_IMG_ROWS; ++r)
    {
      for (uint8_t c = 0; c < POOL_IMG_COLS; ++c)
      {
        printf("%.0f ", pool_features[r][c][f]);
      }
      printf("\n");
    }
  }
}
#endif
