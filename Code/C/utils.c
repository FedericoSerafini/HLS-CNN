#include "definitions.h"
#include "utils.h"
#include "float.h"

#include <stdio.h>

void
normalize
(
  const float img_in  [IMG_ROWS][IMG_COLS],
  float       img_out [IMG_ROWS][IMG_COLS]
)
{
  for (uint8_t i = 0; i < IMG_ROWS; ++i)
    for(uint8_t j = 0; j < IMG_COLS; ++j)
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
max_pooling
(
  const float img_in[IMG_ROWS][IMG_COLS],
  float       img_out[IMG_ROWS / POOL_SIZE][IMG_COLS / POOL_SIZE]
)
{
  float pool = 0.0;
  float tmp  = 0.0;

  for(uint8_t i = 0; i < IMG_ROWS; i += POOL_SIZE)
    for(uint8_t j = 0; j < IMG_COLS; j += POOL_SIZE)
    {
      pool = FLT_MIN;

      for (uint8_t pi = 0; pi < POOL_SIZE; ++pi)
        for (uint8_t pj = 0; pj < POOL_SIZE; ++pj)
        {
          tmp = img_in[i + pi][j + pj];
          if (tmp > pool)
            pool = tmp;
        }

      img_out[i / POOL_SIZE][j / POOL_SIZE] = pool;
    }
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

void
print_pool_img(const float img[IMG_ROWS / POOL_SIZE][IMG_COLS / POOL_SIZE])
{
  for (uint8_t i = 0; i < IMG_ROWS / POOL_SIZE; ++i)
  {
    for (uint8_t j = 0; j < IMG_COLS / POOL_SIZE; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}
