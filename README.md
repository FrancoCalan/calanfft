# calanfft

This project is an attempt to implement the FFT algorithm
using Xilinx HLS (High-Level Synthesis) for the Virtex-6 FPGA.
The final goal of this project is to give an alternative for
spectrometer programming for the ROACH1/ROACH2 platform (see
https://casper.berkeley.edu).

## Sub-projects
- **butterfly_dif:**: implementation of DiF (decimation in frequency) butterfly of FFT. This is the most atomic component
of an FFT.
- **butterfly_loop:**: first loop of FFT that iterates over
butterfies.
- **twiddles_loop:** second loop of FFT that iterated over 
twiddles factors.
- **calanfft:** first implementation of FFT. Simple code but the
implementation is not streaming (can't receive inputs every
clock cycle).
- **calanfft2:** streaming implementation of FFT. Still 
inefficient implementation, specially in the use of memory.
- **calanfft3:** attempt to reduce memory usage by computing 
twiddle factors, instead of loading them to ROM. Has more
quantization error. Better to use calanfft2.
- **pp4fpgas:** copy of another FFT implementation used for help.
Extracted from here: https://github.com/KastnerRG/pp4fpgas
- **tw_generator:** python script for the generation of twiddle
factors into a file. Used to later be loaded as ROM in FFT
implementations.
