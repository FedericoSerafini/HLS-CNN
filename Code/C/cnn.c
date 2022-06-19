#include "cnn.h"
#include "utils.h"
#include "activ_fun.h"
#include "conv.h"
#include "pool.h"
#include "flat.h"
#include "dense.h"

#ifndef __SYNTHESIS__
# include <stdio.h>
#endif

void cnn(const float img_in [IMG_ROWS][IMG_COLS], float prediction[DIGITS])
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
    FILTERS resulting feature maps, one for each filter.
  */
  float conv_image [FILTERS][IMG_ROWS][IMG_COLS];

  // Apply a convolution operation for each filter.
  for(uint8_t kf = 0; kf < FILTERS; ++kf)
    conv(pad_img, kf, conv_image[kf]);

  #ifndef __SYNTHESIS__
  // Print results.
  for(uint8_t f = 0; f < FILTERS; ++f)
  {
    printf("Conv layer filter %d.\n", f);
    print_img(conv_image[f]);
  }
  #endif

  /******** Maxpooling layer. ********/
  float pool_image [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS];

  // Apply a max pooling operation for each filter.
  for(uint8_t kf = 0; kf < FILTERS; ++kf)
    max_pooling(conv_image[kf], pool_image[kf]);

  #ifndef __SYNTHESIS__
  // Print results.
  for(uint8_t f = 0; f < FILTERS; ++f)
  {
    printf("Max pool layer filter %d.\n", f);
    print_pool_img(pool_image[f]);
  }
  #endif

  /******** Flatten layer. ********/
  float flat_image [FLAT_SIZE];
  flatten(pool_image, flat_image);

  /******** Dense layer 1 ********/
  float dense1_image [DENSE1_SIZE];
  dense1(flat_image, dense1_image);

  /******** Dense layer 2 ********/
  dense2(dense1_image, prediction);

}