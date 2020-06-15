#include "twiddles_loop.h"

void btfly1(dtype x0r,  dtype x0i,
            dtype x1r,  dtype x1i,
            wtype wr,   dtype wi,
            dtype *y0r, dtype *y0i,
            dtype *y1r, dtype *y1i) {

	*y0r = x0r + x1r;
    *y0i = x0i + x1i;
    *y1r = wr*(x0r - x1r) - wi*(x0i - x1i);
    *y1i = wr*(x0i - x1i) + wi*(x0r - x1r);
}

void btfly2(dtype x0r,  dtype x0i,
            dtype x1r,  dtype x1i,
            wtype wr,   dtype wi,
            dtype *y0r, dtype *y0i,
            dtype *y1r, dtype *y1i) {

    dtype xar = x0r + x1r; // x addition real
	dtype xai = x0i + x1i; // x addition imaginary
	dtype xdr = x0r - x1r; // x difference real
	dtype xdi = x0i - x1i; // x difference imaginary

    // Lyons method variables
    // a=xdr; b=xdi; c=wr; d=di
	dtype k1 = xdr*(wr  + wi );
	dtype k2 = wi *(xdr + xdi);
	dtype k3 = wr *(xdi - xdr);

    *y0r = xar;
    *y0i = xai;
    *y1r = k1 - k2;
    *y1i = k1 + k3;
}
