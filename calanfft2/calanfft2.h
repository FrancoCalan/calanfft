#ifndef _CALANFFT2_H_
#define _CALANFFT2_H_

#include <ap_int.h>

typedef ap_fixed<18,1> dtype;
typedef ap_fixed<18,2> wtype;

// variables that must be changed manually
#define SIZE 1024      // FFT size
#define STAGES 10      // = log2(SIZE)
#include "twiddle_factors/w_1024_r.h"
#include "twiddle_factors/w_1024_i.h"

// functions declarations
void get_twiddles1(int n, int i, wtype *wr, wtype *wi);
void btfly1(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void btfly2(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void calanfft2(dtype xr[SIZE], dtype xi[SIZE],
               dtype yr[SIZE], dtype yi[SIZE]);
#endif // _CALANFFT2_H_
