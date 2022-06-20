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
  float norm_img [IMG_ROWS][IMG_COLS] = { 0 };
  normalize(img_in, norm_img);

  #if 0
  #ifndef __SYNTHESIS__
    print_img(norm_img);
      printf("Normalized image.\n");
    #endif
  #endif

  /******** Padding. ********/
  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS] = { 0 };
  padding(norm_img, pad_img);

  #if 0
    #ifndef __SYNTHESIS__
      printf("Padded image.\n");
      print_pad_img(pad_img);
    #endif
  #endif

  /******** Convolution layer 1. ********/
  /*
    An array to collect the results of the convolutions:
    FILTERS resulting feature maps, one for each filter.
  */
  float features [IMG_ROWS][IMG_COLS][FILTERS] = { 0 };

  conv(pad_img, features);

  #if 0
    #ifndef __SYNTHESIS__
    // Print results.
    print_features(features);
    #endif
  #endif

  /******** Maxpooling layer. ********/
  float pool_features [POOL_IMG_ROWS][POOL_IMG_COLS][FILTERS] = { 0 };

  max_pooling(features, pool_features);

  #if 0
    #ifndef __SYNTHESIS__
      print_pool_features(pool_features);
    #endif
  #endif

  /******** Flatten layer. ********/
  float flat_array [FLAT_SIZE] = { 0 };
  flatten(pool_features, flat_array);

  /******** Dense layer 1 ********/
  float dense1_array [DENSE1_SIZE] = { 0 };
  dense1(flat_array, dense1_array);
  float dense1_relu [DENSE1_SIZE] = { 0 };
  relu_on_dense1(dense1_array, dense1_relu);

  /******** Dense layer 2 ********/
  float dense2_array [DIGITS] = { 0 };
  dense2(dense1_relu, dense2_array);
  // Get a prediction applying softmax.
  soft_max(dense2_array, prediction);

}
