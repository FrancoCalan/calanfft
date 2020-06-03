#include "butterfly.h"

void btfly1(dtype x0r,  dtype x0i,
            dtype x1r,  dtype x1i,
            wtype wr,   dtype wi,
            dtype *y0r, dtype *y0i,
            dtype *y1r, dtype *y1i) {
    /**
     * Performs the butterfly operation of a DiF FFT
     * (Decimation in Frequency Fast Fourer Transform),
     * that is, y0 = x0 + x1, and y1 = w*(x0 - x1), where
     * all variables are complex.
     *
     * @param x0r First input real part
     * @param x0i First input imaginary part
     * @param x1r Second input real part
     * @param x1i Second input imaginary part
     * @param wr  Twiddle factor real part 
     * @param wi  Twiddle factor imaginary part
     * @param y0r First output real part
     * @param y0i First output imaginary part
     * @param y1r Second output real part
     * @param y1i Second output imaginary part
     */
	#pragma HLS PIPELINE
	#pragma HLS INTERFACE ap_none port=y0r
	#pragma HLS INTERFACE ap_none port=y0i
	#pragma HLS INTERFACE ap_none port=y1r
	#pragma HLS INTERFACE ap_none port=y1i
	#pragma HLS INTERFACE ap_ctrl_none port=return

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
    /**
     * Same as btfly1 but use Lyons method from book 
     * Understanding Digital Signal Processing (ed. 3 pg. 602)
     * to do 3 multiplications instead of 4.
     *
     * @param x0r First input real part
     * @param x0i First input imaginary part
     * @param x1r Second input real part
     * @param x1i Second input imaginary part
     * @param wr  Twiddle factor real part 
     * @param wi  Twiddle factor imaginary part
     * @param y0r First output real part
     * @param y0i First output imaginary part
     * @param y1r Second output real part
     * @param y1i Second output imaginary part
     */
	#pragma HLS PIPELINE
	#pragma HLS INTERFACE ap_none port=y0r
	#pragma HLS INTERFACE ap_none port=y0i
	#pragma HLS INTERFACE ap_none port=y1r
	#pragma HLS INTERFACE ap_none port=y1i
	#pragma HLS INTERFACE ap_ctrl_none port=return

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
