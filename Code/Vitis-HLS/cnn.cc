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

void
dataflow_section
(
  float pad_img  [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img1 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img2 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img3 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float prediction [DIGITS]
)
{
  /******** Convolution layer. ********/
  /*
    An array to collect the convolution results:
    FILTERS resulting feature maps, one for each filter.
  */

  hls::stream<float, IMG_ROWS * IMG_COLS>
  conv_to_pool_streams [FILTERS];

  // Convolution with relu as activation function.
  convolutional_layer(pad_img, pad_img1, pad_img2, pad_img3,
                      conv_to_pool_streams);

  #if 0
    #ifndef __SYNTHESIS__
      // Print results.
      print_features(features);
    #endif
  #endif

  /******** Maxpooling layer. ********/

  hls::stream<float, POOL_IMG_ROWS * POOL_IMG_COLS>
  pool_to_flat_streams[FILTERS];

  max_pooling_layer(conv_to_pool_streams, pool_to_flat_streams);

  #if 0
    #ifndef __SYNTHESIS__
      print_pool_features(pool_to_flat_streams);
    #endif
  #endif

  /******** Flatten layer. ********/
  hls::stream<float, FLAT_SIZE> flat_to_dense_streams [FILTERS];
  flattening_layer(pool_to_flat_streams, flat_to_dense_streams);

  /******** Dense layer ********/
  dense_layer(flat_to_dense_streams, prediction);
}


void cnn
(
  float img_in     [IMG_ROWS][IMG_COLS],
  float prediction [DIGITS]
)
{
  /******** Preprocessing data. ********/

  /* Normalization. */
  float norm_img [IMG_ROWS][IMG_COLS];
  normalize(img_in, norm_img);

  #if 0
    #ifndef __SYNTHESIS__
      printf("Normalized image.\n");
      print_img(norm_img);
    #endif
  #endif

  /* Padding. */
  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS];
  padding(norm_img, pad_img);

  #if 0
    #ifndef __SYNTHESIS__
      printf("Padded image.\n");
      print_pad_img(pad_img);
    #endif
  #endif

  /* Allow parallelism cloning the padded image. */
  float pad_img1 [PAD_IMG_ROWS][PAD_IMG_COLS];
  float pad_img2 [PAD_IMG_ROWS][PAD_IMG_COLS];
  float pad_img3 [PAD_IMG_ROWS][PAD_IMG_COLS];
  clone(pad_img, pad_img1);
  clone(pad_img, pad_img2);
  clone(pad_img, pad_img3);

  /* Parallel executions start here. */
  dataflow_section(pad_img, pad_img1, pad_img2, pad_img3, prediction);

}
