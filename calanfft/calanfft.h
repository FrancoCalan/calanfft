#ifndef _CALANFFT_H_
#define _CALANFFT_H_

#include <ap_int.h>

typedef ap_fixed<18,1> dtype;
typedef ap_fixed<18,2> wtype;

// variables that must be changed manually
#define SIZE   8   // FFT size
#define STAGES 3     // = log2(SIZE)
#include "w_8_r.h" // twiddle factors real
#include "w_8_i.h" // twiddle factors imaginary

// functions declarations
void get_twiddles1(int n, int i, wtype *wr, wtype *wi);
void btfly1(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void btfly2(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void calanfft(dtype xr[SIZE], dtype xi[SIZE],
              dtype yr[SIZE], dtype yi[SIZE]);
#endif // _CALANFFT_H_
