#include "cnn.hh"
#include "utils.hh"
#include "activ_fun.hh"
#include "conv.hh"
#include "pool.hh"
#include "flat.hh"
#include "dense.hh"

#include "hls_stream.h"

#ifndef __SYNTHESIS__
# include <cstdio>
#endif

void cnn
(
  float img_in     [IMG_ROWS][IMG_COLS],
  float prediction [DIGITS]
)
{

  /******** Normalization. ********/
  float norm_img [IMG_ROWS][IMG_COLS];
  normalize(img_in, norm_img);

  #if 0
    #ifndef __SYNTHESIS__
      printf("Normalized image.\n");
      print_img(norm_img);
    #endif
  #endif


  /******** Padding. ********/
  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS];
  padding(norm_img, pad_img);

  #if 0
    #ifndef __SYNTHESIS__
      printf("Padded image.\n");
      print_pad_img(pad_img);
    #endif
  #endif

  /******** Convolution layer. ********/
  /*
    An array to collect the convolution results:
    FILTERS resulting feature maps, one for each filter.
  */

  // float features [FILTERS][IMG_ROWS][IMG_COLS];
  hls::stream<float> stream_conv_to_pool;
  // Convolution with relu as activation function.
  conv_layer(pad_img, stream_conv_to_pool);

  #if 0
    #ifndef __SYNTHESIS__
      // Print results.
      print_features(features);
    #endif
  #endif

  /******** Maxpooling layer. ********/

  // float pool_features [FILTERS][POOL_IMG_ROWS][POOL_IMG_COLS];
  hls::stream<float> stream_pool_to_flat;
  max_pooling_layer(stream_conv_to_pool, stream_pool_to_flat);

  #if 0
    #ifndef __SYNTHESIS__
      print_pool_features(pool_features);
    #endif
  #endif

  /******** Flatten layer. ********/
  //float flat_array [FLAT_SIZE];
  hls::stream<float> stream_flat_to_dense;
  flattening_layer(stream_pool_to_flat, stream_flat_to_dense);

  /******** Dense layer ********/
  dense_layer(stream_flat_to_dense, prediction);

}
