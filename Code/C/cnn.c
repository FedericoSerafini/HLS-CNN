#include "cnn.h"
#include "utils.h"
#include "activ_fun.h"
#include "conv.h"

void cnn(const float img_in [IMG_ROWS][IMG_COLS], float pred[10])
{
  /******** Normalization. ********/
  printf("Normalized image.\n");
  float norm_img [IMG_ROWS][IMG_COLS];
  normalize(img_in, norm_img);
  print_img(norm_img);

  /******** Padding. ********/
  printf("Padded image.\n");
  float pad_img [IMG_ROWS + 2][IMG_COLS + 2];
  padding(norm_img, pad_img);
  print_pad_img(pad_img);

  /******** Convolution layer 1. ********/
  /*
    An array to collect the results of the convolutions:
    KRN_FILTERS result images, one for each filter.
  */
  float conv1_images [KRN_FILTERS][IMG_ROWS][IMG_COLS];

  // Apply a convolution operation for each filter.
  for(uint8_t kf = 0; kf < KRN_FILTERS; ++kf)
    conv(pad_img, kf, conv1_images[kf]);

  // Print results.
  for(int f = 0; f < KRN_FILTERS; ++f)
  {
    printf("Conv layer 1, filter %d.\n", f);
    print_img(conv1_images[f]);
  }


  /******** Output. ********/
  for(int i = 0; i < 10; ++i)
  {
    pred[i] = 0.0;
  }

}