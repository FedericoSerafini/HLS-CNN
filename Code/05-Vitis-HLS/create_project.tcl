################################################################################
## Create the Vitis HLS project using the following command:
## $ vitis_hls -f create_project.tcl
################################################################################

open_project Project
set_top cnn
add_files cnn.cc
add_files conv.cc
add_files dense.cc
add_files flat.cc
add_files pool.cc
add_files utils.cc
add_files -tb cnn_tb.cc
add_files -tb ../02-Data
open_solution "solution1" -flow_target vivado
set_part {xc7a200tfbg484-1}
create_clock -period 10 -name default
source "directives.tcl"
