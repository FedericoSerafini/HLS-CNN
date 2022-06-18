#include "cnn.h"
#include "utils.h"

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

// FIXME: remove all print from utils.

int main ()
{
  // Read the image.
  float img [IMG_ROWS][IMG_COLS];
  read_img("../Data/image.txt", img);

  // Prepare array for output.
  float pred [10];

  cnn(img, pred);

  return 0;
}
