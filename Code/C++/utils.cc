#include "definitions.hh"
#include "utils.hh"

#ifndef __SYNTHESIS__
# include <cstdio>
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
  for (int r = 0; r < IMG_ROWS; ++r)
  {
    norm_for_cols:
    for(int c = 0; c < IMG_COLS; ++c)
    {
      img_out[r][c] = img_in[r][c] / 255.0;
    }
  }
}

void
padding
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
}

void
clone
(
  float img_in [PAD_IMG_ROWS][PAD_IMG_COLS],
  float images [FILTERS][PAD_IMG_ROWS][PAD_IMG_COLS]
)
{
  for (int f = 0; f < FILTERS; ++f)
    for (int r = 0; r < PAD_IMG_ROWS; ++r)
      for (int c = 0; c < PAD_IMG_COLS; ++c)
      {
        images[f][r][c] = img_in[r][c];
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
