############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Project
set_top cnn
add_files activ_fun.cc
add_files cnn.cc
add_files conv.cc
add_files dense.cc
add_files flat.cc
add_files pool.cc
add_files utils.cc
add_files -tb cnn_tb.cc
add_files -tb ../Data/image.txt
open_solution "solution1" -flow_target vivado
set_part {xc7a35ticpg236-1L}
create_clock -period 10 -name default
source "./Project/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
