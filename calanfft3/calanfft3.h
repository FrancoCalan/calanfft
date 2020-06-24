#ifndef _CALANFFT3_H_
#define _CALANFFT3_H_

#include <ap_int.h>
#include <math.h>

typedef ap_fixed<18,1> dtype;
typedef ap_fixed<18,2> wtype;

// variables that must be changed manually
#define SIZE 16384     // FFT size
#define STAGES 14      // = log2(SIZE)

// functions declarations
void btfly1(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void btfly2(dtype x0r,  dtype x0i, dtype x1r,  dtype x1i,
            wtype wr,   wtype wi,
            dtype *y0r, dtype *y0i, dtype *y1r, dtype *y1i);
void twiddle_mtply(wtype *wr, wtype *wi,
                    wtype wrs, wtype wis);
void calanfft3(dtype xr[SIZE], dtype xi[SIZE],
               dtype yr[SIZE], dtype yi[SIZE]);
#endif // _CALANFFT3_H_
