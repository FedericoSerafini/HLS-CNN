#include "cnn.h"

#include <string.h>
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

  double latency = 0.0;
  float images [DIGITS][IMG_ROWS][IMG_COLS];

  for (int i = 0; i < DIGITS; ++i)
  {

    /**** Read the image. ****/

    char file_path [32] = "../Data/image";
    char str [8];
    sprintf(str, "%d.txt", i);
    strcat(file_path, str);

    if (0 != read_img(file_path, images[i]))
    {
      printf("Error: can't open file.\n");
      return 1;
    }

    // Prepare array for output.
    float prediction [DIGITS];

    /**** CNN execution, obtain a prediction. ****/
    clock_t begin = clock();
    cnn(images[i], prediction);
    clock_t end = clock();

    printf("\nPrediction %d:\n", i);
    for (int j = 0; j < DIGITS; ++j)
    printf("%d: %.2f\n", j, prediction[j]);

    latency += (double)(end - begin) / CLOCKS_PER_SEC;
  }

  latency = latency / DIGITS;
  printf("\nAverage latency: %f (s)\n", latency);
  printf("\n");

  return 0;
}
