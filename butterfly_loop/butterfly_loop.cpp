#include "butterfly.h"

# define N 4096

void btfly_loop(dtype x0r[N], dtype x0i[N],
                dtype x1r[N], dtype x1i[N],
                wtype wr,     dtype wi,
                dtype y0r[N], dtype y0i[N],
                dtype y1r[N], dtype y1i[N]) {

    /**
     * Performs the innermore loop of an FFT, which
     * basically consists in fixing a twiddle factor,
     * and computes the butterfly through an array of 
     * input.
     * @param x0r First input array real part
     * @param x0i First input array imaginary part
     * @param x1r Second input array real part
     * @param x1i Second input array imaginary part
     * @param wr  Twiddle factor real part 
     * @param wi  Twiddle factor imaginary part
     * @param y0r First output array real part
     * @param y0i First output array imaginary part
     * @param y1r Second output array real part
     * @param y1i Second output array imaginary part
     */
	//#pragma HLS INTERFACE ap_ctrl_none port=return
	//#pragma HLS PIPELINE II=1
	//#pragma HLS DATAFLOW
	//#pragma HLS INTERFACE ap_fifo depth=1 port=x0r
	//#pragma HLS INTERFACE ap_fifo depth=1 port=x0i
	//#pragma HLS INTERFACE ap_fifo depth=1 port=x1r
	//#pragma HLS INTERFACE ap_fifo depth=1 port=x1i
	//#pragma HLS INTERFACE ap_fifo depth=1 port=y0r
	//#pragma HLS INTERFACE ap_fifo depth=1 port=y0i
	//#pragma HLS INTERFACE ap_fifo depth=1 port=y1r
	//#pragma HLS INTERFACE ap_fifo depth=1 port=y1i
	//#pragma HLS STREAM variable=x0r depth=1 dim=1
	//#pragma HLS STREAM variable=x0i depth=1 dim=1
	//#pragma HLS STREAM variable=x1r depth=1 dim=1
	//#pragma HLS STREAM variable=x1i depth=1 dim=1
	//#pragma HLS STREAM variable=y0r depth=1 dim=1
	//#pragma HLS STREAM variable=y0i depth=1 dim=1
	//#pragma HLS STREAM variable=y1r depth=1 dim=1
	//#pragma HLS STREAM variable=y1i depth=1 dim=1

	loop: for (int i=0; i<N; ++i) {
		#pragma HLS PIPELINE II=1 rewind
        btfly2(x0r[i], x0i[i],
               x1r[i], x1i[i],
               wr,     wi,
               &y0r[i], &y0i[i],
               &y1r[i], &y1i[i]);
    }
}
