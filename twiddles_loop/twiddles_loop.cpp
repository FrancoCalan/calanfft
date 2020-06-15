#include <ap_int.h>

typedef ap_fixed<18,1> dtype;
typedef ap_fixed<18,1> wtype;

// variables that must be changed manually
#define SIZE  1024    // FFT size
#define STAGE 3       // FFT stage [0, ..., log2(N)-1]
#include "w_1024_r.h" // twiddle factors real
#include "w_1024_i.h" // twiddle factors imaginary

void twiddles_loop(dtype xr[N], dtype xi[N],
                   dtype yr[N], dtype yi[N]) {

    int n = 1 << STAGE;    //number of stage subffts
    int m = SIZE >> STAGE; // size of stage subffts

    for(int i=0; i<m/2; ++i) {
        wtype wr; wtype wi;
        get_twiddles1(n, i, &wr, &wi);

        for (int j1=0; j1<SIZE; j1+=m) {
            j2 = j1 + m/2; // index of btfly 2nd input
            btlfy2(xr[j1], xi[j1], xr[j2], xi[j2], wr, wi,
                   yr[j1], yi[j1], yr[j2], yi[j2]);
        }
    }
}

void get_twiddles1(int n, int i, wtype *wr, wtype, *wi) {
    wr = wr_arr[i*n];
    wi = wi_arr[i*n];
}

void btfly1(dtype x0r,  dtype x0i,
            dtype x1r,  dtype x1i,
            wtype wr,   dtype wi,
            dtype *y0r, dtype *y0i,
            dtype *y1r, dtype *y1i) {
	//#pragma HLS PIPELINE

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
	//#pragma HLS PIPELINE
	
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
