#include "definitions.h"
#include "utils.h"

#include <stdio.h>

void
normalize
(
  const float img_in  [IMG_ROWS][IMG_COLS],
  float       img_out [IMG_ROWS][IMG_COLS]
)
{
  for (int i = 0; i < IMG_ROWS; ++i)
    for(int j = 0; j < IMG_COLS; ++j)
      img_out[i][j] = img_in[i][j] / 255.0;
}

void
padding
(
  const float img_in [IMG_ROWS][IMG_COLS],
  float       img_out [IMG_ROWS + PAD_ROWS][IMG_COLS + PAD_COLS]
)
{
  for(uint8_t i = 0; i < IMG_ROWS + PAD_ROWS; ++i)
    for(uint8_t j = 0; j < IMG_COLS + PAD_COLS; ++j)
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
print_pad_img(const float img[IMG_ROWS + PAD_ROWS][IMG_COLS + PAD_COLS])
{
  for (uint8_t i = 0; i < IMG_ROWS + PAD_ROWS; ++i)
  {
    for (uint8_t j = 0; j < IMG_COLS + PAD_COLS; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}