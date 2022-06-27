#include "cnn.hh"

#include <cstdio>
#include <ctime>

// ATTENTION: N cannot be set greater than the # of images (and labels)
// actually in in.dat and out.dat files.
#define N 100

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

int read_labels(const char * file, int labels[N])
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
    printf("Error: odd kernel sizes are mandatory for .hhis implementation \n");
    return 1;
  }

  // O.hher .hhecks needed?
  // Will convolution work wi.hh KRN_ROWS != KRN_COLS?
  // Same question for IMG_ROWS and COLS.

  /**** Read the images. ****/
  float images[N][IMG_ROWS][IMG_COLS];
  if (0 != read_images("in.dat", images))
  {
    printf("Error: can't open in.dat file.\n");
    return 1;
  }

  /**** Read expected labels. ****/
  int labels[N];
  if (0 != read_labels("out.dat", labels))
  {
    printf("Error: can't open out.dat file.\n");
    return 1;
  }

  /**** Do N predictions. ****/
  double times_sum = 0;
  int correct_predictions = 0;

  for (int i = 0; i < N; ++i)
  {
    // Prepare array for output.
    float prediction [DIGITS];

    // CNN execution, obtain a prediction.
    clock_t begin = clock();
    cnn(images[i], prediction);
    clock_t end = clock();

    //printf("\nPrediction: %d", get_max_prediction(prediction));
    //printf("\nExpected: %d", labels[i]);

    if (get_max_prediction(prediction) == labels[i])
    {
      ++correct_predictions;
    }
    //for (int i = 0; i < DIGITS; ++i)
    //{
    //  printf("%d: %.2f\n", i, prediction[i]);
    //}

    // Add time spent.
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("\nTime spent: %f (s)\n", time_spent);
    times_sum += time_spent;
  }

  double correct_predictions_perc = correct_predictions * 100 / N;
  printf("Correct predictions (%%): %.2f\n", correct_predictions_perc);
  printf("Time spent avg (ms): %f\n", (times_sum / N) * 1000);

  // Test is considered successfull if % of correct predictions
  // is more than 95%.
  if (correct_predictions_perc >= 95.00)
	  return 0;
  return -1;
}
