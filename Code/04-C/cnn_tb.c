#include "cnn.h"
#include "utils.h"

#include <stdio.h>
#include <time.h>

#define N 1000

int
read_images (const char * file, float images [N][IMG_ROWS][IMG_COLS])
{
  FILE *fp;

  fp = fopen(file, "r");

  if (fp == NULL)
    return -1;

  for (int i = 0; i < N; ++i)
    for (int x = 0; x < IMG_ROWS; ++x)
      for (int y = 0; y < IMG_COLS; ++y)
        if(fscanf(fp, "%f", & images[i][x][y]) != 1)
          return 1; // Error.

  return fclose(fp);
}

int
read_labels(const char * file, int labels[N])
{
  FILE *fp;

  fp = fopen(file, "r");

  if (fp == NULL)
    return -1;

  for (int i = 0; i < N; ++i)
    if(fscanf(fp, "%d", & labels[i]) != 1)
      return 1;

  return fclose(fp);
}

int
get_max_prediction (float prediction [DIGITS])
{
  int max_digit = 0;
  for (int i = 0; i < DIGITS; ++i)
  {
    if (prediction[i] > prediction[max_digit])
      max_digit = i;
  }
  return max_digit;
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

  /**** Read the images. ****/
  float images[N][IMG_ROWS][IMG_COLS];
  if (0 != read_images("../02-Data/in.dat", images))
  {
    printf("Error: can't open file ``../02-Data/in.dat''\n");
    return 1;
  }

  /**** Read expected labels. ****/
  int labels[N];
  if (0 != read_labels("../02-Data/out.dat", labels))
  {
    printf("Error: can't open file ``../02-Data/out.dat''\n");
    return 1;
  }

  /**** Do N predictions. ****/
  double time = 0;
  int correct_predictions = 0;
  float prediction [DIGITS];

  for (int i = 0; i < N; ++i)
  {
    // CNN execution, obtain a prediction.
    clock_t begin = clock();
    cnn(images[i], prediction);
    clock_t end = clock();

    if (get_max_prediction(prediction) == labels[i])
    {
      ++correct_predictions;
    }
    else
    {
      printf("\nExpected: %d\n", labels[i]);
      float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS];
      normalization_and_padding(images[i], pad_img);
      print_pad_img(pad_img);
      printf("Wrong prediction:\n");
      for (int j = 0; j < DIGITS; ++j)
        printf("%d: %f\n", j, prediction[j]);
      printf("\n********************************\n");
    }

    // Sum up time spent.
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time += time_spent;
  }

  double
  correct_predictions_perc = (double)correct_predictions * 100.0 / (double)N;
  printf("\nTotal predictions: %d\n", N);
  printf("Correct predictions: %.2f %%\n", correct_predictions_perc);
  printf("Average latency: %f (ms)\n", (time / N) * 1000);

  return 0;
}
