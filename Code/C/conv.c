#include "conv.h"
#include "definitions.h"

void
conv
(
  const float img_in[IMG_ROWS + 2][IMG_COLS + 2],
  const float kernel[KERNEL_ROWS][KERNEL_COLS],
  float       img_out[IMG_ROWS][IMG_COLS])
{

  for(int i = 0; i < IMG_ROWS; ++i)
    for(int j = 0; j < IMG_COLS; ++j)
    {
      float sum = 0;

      for(int ki = 0; ki < KERNEL_ROWS; ++ki)
        for(int kj = 0; kj < KERNEL_COLS; ++kj)
        {
          sum += kernel[ki][kj] * img_in[i+ki][j+kj];
        }

     img_out[i][j] = sum;
    }
}
