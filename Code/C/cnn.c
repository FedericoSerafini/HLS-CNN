#include "cnn.h"
#include "utils.h"


int8_t cnn()
{

  float img [IMG_ROWS][IMG_COLS];
  read_img("../Data/image.txt", img);
  print_img(img);

  float norm_img [IMG_ROWS][IMG_COLS];
  normalize(img, norm_img);
  print_img(norm_img);

  float pad_img [IMG_ROWS+1][IMG_COLS+1];
  padding(norm_img, pad_img);
  print_pad_img(pad_img);

  return 0;
}