############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name cnn "cnn"
set_directive_dataflow "dataflow_section"
set_directive_dataflow "convolutional_layer"
set_directive_dataflow "max_pooling_layer"
set_directive_dataflow "flattening_layer"
set_directive_dataflow "dense_layer"
set_directive_pipeline -II 32 "convolution/conv_for_cols"
set_directive_pipeline -II 4 "max_pooling/pool_for_cols"
set_directive_pipeline -II 10 "dense/dense_for_flat"
