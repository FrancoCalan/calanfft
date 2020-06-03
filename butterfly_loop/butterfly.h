#ifndef BUTTERFLY_H_
#define BUTTERFLY_H_

#include <ap_int.h>

typedef ap_int<18> dtype;
typedef ap_int<18> wtype;

void btfly1(dtype x0r, dtype x0i,
            dtype x1r, dtype x1i,
            wtype wr,  dtype wi,
            dtype *y0r, dtype *y0i,
            dtype *y1r, dtype *y1i);
 
void btfly2(dtype x0r, dtype x0i,
            dtype x1r, dtype x1i,
            wtype wr,  dtype wi,
            dtype *y0r, dtype *y0i,
            dtype *y1r, dtype *y1i);

#endif # BUTTERFLY_H_
