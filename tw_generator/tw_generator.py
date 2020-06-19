#!/usr/bin/python
import argparse
import numpy as np

# command line parser
parser = argparse.ArgumentParser(
    description="Create C header files (.h) with twiddle " \
    "factor constants for the implementation of FFT " \
    "algorithms.")
parser.add_argument("N", type=int,
    help="Size of the FFT to implement. The number of " \
    "twiddle factors generated is equal to half of this " \
    "size: W_N^0 ... W_N^{N/2-1}")
args = parser.parse_args()

# compute twiddle factors
n = np.arange(args.N//2)
w_arr = np.exp(-1j*2*np.pi*n/args.N)

# real part of twiddle factors
with open("../calanfft2/twiddle_factors/w_" + str(args.N) + "_r.h", "w") as f:
    f.write("const wtype wr_arr[] = {\n");
    for w in w_arr:
        f.write("{0:+.20f}".format(float(np.real(w))) + ",\n")
    f.write("};")

# imaginary part of twiddle factors
with open("../calanfft2/twiddle_factors/w_" + str(args.N) + "_i.h", "w") as f:
    f.write("const wtype wi_arr[] = {\n");
    for w in w_arr:
        f.write("{0:+.20f}".format(float(np.imag(w))) + ",\n")
    f.write("};")
