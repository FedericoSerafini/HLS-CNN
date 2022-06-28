#include "cnn.hh"

#include <cstdio>
#include <ctime>

#define N 10

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
        fscanf(fp, "%f", & images[i][x][y]);

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
    fscanf(fp, "%d", & labels[i]);

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
  if (0 != read_images("Data/in.dat", images))
  {
    printf("Error: can't open file ``Data/in.dat''\n");
    return 1;
  }

  /**** Read expected labels. ****/
  int labels[N];
  if (0 != read_labels("Data/out.dat", labels))
  {
    printf("Error: can't open file ``Data/out.dat''\n");
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
        for (int j = 0; j < DIGITS; ++j)
          printf("%d: %f\n", j, prediction[j]);
    }

    // Sum up time spent.
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time += time_spent;
  }

  double correct_predictions_perc = correct_predictions * 100.0 / (double)N;
  printf("Total predictions: %d\n", N);
  printf("Correct predictions: %.2f %%\n", correct_predictions_perc);
  printf("Average latency: %f (ms)\n", (time / N) * 1000);

  return 0;
}
