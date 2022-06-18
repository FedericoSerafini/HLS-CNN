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
  float pad_img [IMG_ROWS + PAD_ROWS][IMG_COLS + PAD_COLS];
  padding(norm_img, pad_img);
  print_pad_img(pad_img);

  /******** Convolution layer 1. ********/
  /*
    An array to collect the results of the convolutions:
    KRN_FILTERS result images, one for each filter.
  */
  float conv_images [KRN_FILTERS][IMG_ROWS][IMG_COLS];

  // Apply a convolution operation for each filter.
  for(uint8_t kf = 0; kf < KRN_FILTERS; ++kf)
    conv(pad_img, kf, conv_images[kf]);

  // Print results.
  for(uint8_t f = 0; f < KRN_FILTERS; ++f)
  {
    printf("Conv layer filter %d.\n", f);
    print_img(conv_images[f]);
  }

  /******** Maxpooling layer. ********/
  float pool_images [KRN_FILTERS][IMG_ROWS / POOL_SIZE][IMG_COLS / POOL_SIZE];

  // Apply a max pooling operation for each filter.
  for(uint8_t kf = 0; kf < KRN_FILTERS; ++kf)
    max_pooling(conv_images[kf], pool_images[kf]);

  // Print results.
  for(uint8_t f = 0; f < KRN_FILTERS; ++f)
  {
    printf("Max pool layer filter %d.\n", f);
    print_pool_img(pool_images[f]);
  }

  /******** Output. ********/
  for(uint8_t i = 0; i < 10; ++i)
  {
    pred[i] = 0.0;
  }

}