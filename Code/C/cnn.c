#include "cnn.h"
#include "utils.h"
#include "conv.h"

// FIXME: remove all print from utils.

int8_t cnn()
{
  // Read the image.
  float img [IMG_ROWS][IMG_COLS];
  read_img("../Data/image.txt", img);

  // Normalization.
  printf("Normalized image.\n");
  float norm_img [IMG_ROWS][IMG_COLS];
  normalize(img, norm_img);
  print_img(norm_img);

  // Padding.
  printf("Padded image.\n");
  float pad_img [IMG_ROWS + 2][IMG_COLS + 2];
  padding(norm_img, pad_img);
  print_pad_img(pad_img);

  // Convolution 1.
  printf("Conv1 image.\n");
  float conv1_img [IMG_ROWS][IMG_COLS];
  float kernel[KERNEL_ROWS][KERNEL_COLS]
    ={
      {0.11, 0.11, 0.11},
      {0.11, 0.11, 0.11},
      {0.11, 0.11, 0.11}
    };
  conv(pad_img, kernel, conv1_img);
  print_img(conv1_img);

  return 0;
}