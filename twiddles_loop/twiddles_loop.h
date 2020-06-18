#ifndef _TWIDDLES_LOOP_H_
#define _TWIDDLES_LOOP_H_

#include <ap_int.h>

typedef ap_fixed<18,1> dtype;
typedef ap_fixed<18,2> wtype;
//typedef float dtype;
//typedef float wtype;

// variables that must be changed manually
#define SIZE  1024    // FFT size
#define STAGE 5       // FFT stage [0, ..., log2(N)-1]
#include "w_1024_r.h" // twiddle factors real
#include "w_1024_i.h" // twiddle factors imaginary

// functions declarations
void get_twiddles1(int n, int i, wtype *wr, wtype *wi);
void btfly1(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void btfly2(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void twiddles_loop(dtype xr[SIZE], dtype xi[SIZE],
                   dtype yr[SIZE], dtype yi[SIZE]);
#endif // _TWIDDLES_LOOP_H_
