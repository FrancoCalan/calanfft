############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project -reset calanfft3
set_top calanfft3
add_files butterfly.cpp
add_files calanfft3.cpp
add_files calanfft3.h
add_files init_twiddles_rom.cpp
add_files -tb calanfft3_tb.cpp
add_files -tb gold_data/gold_1024_x.dat
add_files -tb gold_data/gold_1024_y.dat
add_files -tb gold_data/gold_16384_x.dat
add_files -tb gold_data/gold_16384_y.dat
open_solution -reset "solution1"
set_part {xc6vsx475tff1759-1}
create_clock -period 10 -name default
#source "./calanfft2/solution1/directives.tcl"
csim_design
#csynth_design
#cosim_design -tool xsim
#export_design -format ip_catalog
exit
