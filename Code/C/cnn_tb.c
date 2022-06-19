#include "cnn.h"

#include <stdio.h>
#include <time.h>

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
  /**** Basic parameters check. ****/
  // Enforce odd kernel dimensions.
  if ((0 == (KRN_ROWS % 2)) || (0 == (KRN_COLS % 2)))
  {
    printf("Error: odd kernel sizes are mandatory for this implementation \n");
    return 1;
  }

  if ((28 > IMG_ROWS) || (28 > IMG_COLS))
  {
    printf("Warning: 8 and 16 bit integer types are used, check potential overflows\n");
  }

  // Other checks needed?
  // Will convolution work with KRN_ROWS != KRN_COLS?
  // Same question for IMG_ROWS and COLS.

  /**** Read the image. ****/
  float img [IMG_ROWS][IMG_COLS];
  if (0 != read_img("../Data/image.txt", img))
  {
    printf("Error: can't open file.\n");
    return 1;
  }

  // Prepare array for output.
  float prediction [DIGITS];

  /**** CNN execution, obtain a prediction. ****/
  clock_t begin = clock();
  cnn(img, prediction);
  clock_t end = clock();

  printf("\nPrediction:\n");

  for (int i = 0; i < DIGITS; ++i)
  {
    printf("%d: %.2f\n", i, prediction[i]);
  }

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nTime spent: %f (s)\n", time_spent);
  printf("Clocks per second: %ld\n", CLOCKS_PER_SEC);

  return 0;
}
