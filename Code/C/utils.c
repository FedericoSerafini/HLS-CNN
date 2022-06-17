#include "definitions.h"
#include "utils.h"

#include <stdio.h>

int
read_img(const char * file, float img [IMG_ROWS][IMG_COLS])
{
  FILE *fp;

  fp = fopen(file, "r");

  if(fp == NULL)
    return -1;

  for(int i = 0; i < IMG_ROWS; ++i)
    for(int j = 0; j < IMG_COLS; ++j)
      fscanf(fp, "%f", & img[i][j]);

  return fclose(fp);
}

void
normalize
(
  float  img_in  [IMG_ROWS][IMG_COLS],
  float img_out [IMG_ROWS][IMG_COLS]
)
{
  for (int i = 0; i < IMG_ROWS; ++i)
    for(int j = 0; j < IMG_COLS; ++j)
      img_out[i][j] = img_in[i][j] / 255.0;
}


void
padding
(
  float img_in  [IMG_ROWS][IMG_COLS],
  float img_out [IMG_ROWS + 2][IMG_COLS + 2]
)
{
  for(uint8_t i = 0; i < IMG_ROWS + 2; ++i)
    for(uint8_t j = 0; j < IMG_COLS + 2; ++j)
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
print_pad_img(float img[IMG_ROWS + 2][IMG_COLS + 2])
{
  for (uint8_t i = 0; i < IMG_ROWS + 2; ++i)
  {
    for (uint8_t j = 0; j < IMG_COLS + 2; ++j)
    {
      printf("%.0f", img[i][j]);
    }

    printf("\n");
  }
}