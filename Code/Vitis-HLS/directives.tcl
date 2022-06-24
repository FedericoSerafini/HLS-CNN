############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name cnn "cnn"
set_directive_dataflow "dataflow_section"
set_directive_pipeline -II 5 "convolution/win_for_cols"
set_directive_pipeline -II 10 "dense_layer/dense_for_p"
set_directive_pipeline -II 4 "max_pooling/pool_for_cols"
