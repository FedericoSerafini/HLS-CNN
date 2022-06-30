#include "cnn.hh"
#include "utils.hh"
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
  float pad_img4 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img5 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img6 [PAD_IMG_ROWS][PAD_IMG_COLS],
  float pad_img7 [PAD_IMG_ROWS][PAD_IMG_COLS],
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
                      pad_img4, pad_img5, pad_img6, pad_img7,
                      conv_to_pool_streams);

  #if 0
    #ifndef __SYNTHESIS__
      // Print results.
      print_features(conv_to_pool_streams);
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
  hls::stream<float, FLAT_SIZE / FILTERS> flat_to_dense_streams [FILTERS];
  flattening_layer(pool_to_flat_streams, flat_to_dense_streams);

  /******** Dense layer. ********/
  hls::stream<float, DENSE_SIZE> dense_to_softmax_streams [FILTERS];
  dense_layer(flat_to_dense_streams, dense_to_softmax_streams);

  /******** Softmax. ********/
  dense_layer_soft_max(dense_to_softmax_streams, prediction);
}

void cnn
(
  float img_in     [IMG_ROWS][IMG_COLS],
  float prediction [DIGITS]
)
{
  /******** Pre-processing data. ********/

  float pad_img [PAD_IMG_ROWS][PAD_IMG_COLS];
  normalization_and_padding(img_in, pad_img);

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
  float pad_img4 [PAD_IMG_ROWS][PAD_IMG_COLS];
  float pad_img5 [PAD_IMG_ROWS][PAD_IMG_COLS];
  float pad_img6 [PAD_IMG_ROWS][PAD_IMG_COLS];
  float pad_img7 [PAD_IMG_ROWS][PAD_IMG_COLS];

  float value;

  clone_for_rows:
  for (int i = 0; i < PAD_IMG_ROWS; ++i)
    clone_for_cols:
    for (int j = 0; j < PAD_IMG_COLS; ++j)
    {
      value = pad_img[i][j];
      pad_img1[i][j] = value;
      pad_img2[i][j] = value;
      pad_img3[i][j] = value;
      pad_img4[i][j] = value;
      pad_img5[i][j] = value;
      pad_img6[i][j] = value;
      pad_img7[i][j] = value;
    }

  /* Parallel executions start here. */
  dataflow_section(pad_img, pad_img1, pad_img2, pad_img3,
                   pad_img4, pad_img5, pad_img6, pad_img7,
                   prediction);
}
