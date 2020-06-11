############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project -reset butterfly_dif
set_top btfly3
add_files butterfly.cpp
open_solution -reset "solution1"
set_part {xc6vsx475tff1759-1}
create_clock -period 10 -name default
#source "./butterfly_dif/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format pcore -use_netlist none
