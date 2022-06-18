#include "cnn.h"
#include "utils.h"
#include "activ_fun.h"
#include "conv.h"
#include "pool.h"
#include "flat.h"

#ifndef __SYNTHESIS__
# include <stdio.h>
#endif

void cnn(const float img_in [IMG_ROWS][IMG_COLS], float pred[10])
{
  /******** Normalization. ********/
  #ifndef __SYNTHESIS__
  printf("Normalized image.\n");
  #endif
  float norm_img [IMG_ROWS][IMG_COLS];
  normalize(img_in, norm_img);
  #ifndef __SYNTHESIS__
  print_img(norm_img);
  #endif

  /******** Padding. ********/
  #ifndef __SYNTHESIS__
    printf("Padded image.\n");
  #endif
  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS];
  padding(norm_img, pad_img);
  #ifndef __SYNTHESIS__
  print_pad_img(pad_img);
  #endif

  /******** Convolution layer 1. ********/
  /*
    An array to collect the results of the convolutions:
    KRN_FILTERS result images, one for each filter.
  */
  float conv_images [KRN_FILTERS][IMG_ROWS][IMG_COLS];

  // Apply a convolution operation for each filter.
  for(uint8_t kf = 0; kf < KRN_FILTERS; ++kf)
    conv(pad_img, kf, conv_images[kf]);

  #ifndef __SYNTHESIS__
  // Print results.
  for(uint8_t f = 0; f < KRN_FILTERS; ++f)
  {
    printf("Conv layer filter %d.\n", f);
    print_img(conv_images[f]);
  }
  #endif

  /******** Maxpooling layer. ********/
  float pool_images [KRN_FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS];

  // Apply a max pooling operation for each filter.
  for(uint8_t kf = 0; kf < KRN_FILTERS; ++kf)
    max_pooling(conv_images[kf], pool_images[kf]);

  #ifndef __SYNTHESIS__
  // Print results.
  for(uint8_t f = 0; f < KRN_FILTERS; ++f)
  {
    printf("Max pool layer filter %d.\n", f);
    print_pool_img(pool_images[f]);
  }
  #endif

  /******** Flatten layer. ********/
  float flat_images [FLAT_SIZE];
  flatten(pool_images, flat_images);

  /******** Output. ********/
  for(uint8_t i = 0; i < 10; ++i)
  {
    pred[i] = 0.0;
  }

}