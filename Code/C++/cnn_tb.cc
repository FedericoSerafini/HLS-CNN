#include "cnn.hh"

#include "hls_stream.h"

#include <cstdio>
#include <ctime>

int
read_img (const char * file, float img [IMG_ROWS][IMG_COLS])
{
  FILE *fp;

  fp = fopen(file, "r");

  if (fp == NULL)
    return -1;

  for (int i = 0; i < IMG_ROWS; ++i)
    for (int j = 0; j < IMG_COLS; ++j)
      fscanf(fp, "%f", & img[i][j]);

  return fclose(fp);
}

int main ()
{
  /**** Basic parameters .check. ****/
  // Enforce odd kernel dimensions.
  if ((0 == (KRN_ROWS % 2)) || (0 == (KRN_COLS % 2)))
  {
    printf("Error: odd kernel sizes are mandatory for this implementation \n");
    return 1;
  }

  // Other checks needed?
  // Will convolution work with KRN_ROWS != KRN_COLS?
  // Same question for IMG_ROWS and COLS.

  /**** Read The image. ****/
  float img [IMG_ROWS][IMG_COLS];
  if (0 != read_img("image.txt", img))
  {
    printf("Error: can't open file.\n");
    return 1;
  }

  // Prepare array for output.
  hls::stream<float> prediction [DIGITS];

  /**** CNN execution, obtain a prediction. ****/
  clock_t begin = clock();
  cnn(img, prediction);
  clock_t end = clock();

  printf("\nPrediction:\n");

  for (int i = 0; i < DIGITS; ++i)
  {
    printf("%d: %.2f\n", i, prediction[i].read());
  }

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nTime spent: %f (s)\n", time_spent);
  printf("\n");

  return 0;
}
