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
  // #pragma HLS pipeline off

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
  float features [FILTERS][IMG_ROWS][IMG_COLS];

  // Apply a convolution operation for each filter.
  cnn_for_conv:
  for(uint8_t f1 = 0; f1 < FILTERS; ++f1)
    conv(pad_img, f1, features[f1]);

  #ifndef __SYNTHESIS__
  // Print results.
  cnn_print_conv:
  for(uint8_t f2 = 0; f2 < FILTERS; ++f2)
  {
    printf("Conv layer filter %d.\n", f2);
    print_img(features[f2]);
  }
  #endif

  /******** Maxpooling layer. ********/
  float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS];

  // Apply a max pooling operation for each filter.
  cnn_for_pool:
  for(uint8_t f3 = 0; f3 < FILTERS; ++f3)
    max_pooling(features[f3], pool_features[f3]);

  #ifndef __SYNTHESIS__
  // Print results.
  cnn_for_print:
  for(uint8_t f4 = 0; f4 < FILTERS; ++f4)
  {
    printf("Max pool layer filter %d.\n", f4);
    print_pool_img(pool_features[f4]);
  }
  #endif

  /******** Flatten layer. ********/
  float flat_array [FLAT_SIZE];
  flatten(pool_features, flat_array);

  /******** Dense layer 1 ********/
  float dense1_array [DENSE1_SIZE];
  dense1(flat_array, dense1_array);

  /******** Dense layer 2 ********/
  float dense2_array [DIGITS];
  dense2(dense1_array, dense2_array);
  // Get a prediction applying softmax.
  soft_max(dense2_array, prediction);

}
