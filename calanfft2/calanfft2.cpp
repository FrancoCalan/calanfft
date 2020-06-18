#include "calanfft2.h"

void fft_stage(int stage,
               dtype xr[SIZE], dtype xi[SIZE],
               dtype yr[SIZE], dtype yi[SIZE]) {
    int n = 1 << stage;    //number of stage subffts
    int m = SIZE >> stage; // size of stage subffts

    twiddles_loop: for(int i=0; i<m/2; i++) {
    	wtype wr; wtype wi;
    	get_twiddles1(n, i, &wr, &wi);

    	btfly_loop: for(int j=0; j<n; j++) {
        	#pragma HLS PIPELINE

			int k1 = j*m + i;  // index of btfly 1st input
        	int k2 = k1 + m/2; // index of btfly 2nd input
            btfly2(xr[k1], xi[k1], xr[k2], xi[k2], wr, wi,
                   &yr[k1], &yi[k1], &yr[k2], &yi[k2]);
        }
    }
}

void fft_stage_first(dtype xr[SIZE], dtype xi[SIZE],
                     dtype yr[SIZE], dtype yi[SIZE]) {

    twiddles_loop: for(int i=0; i<SIZE/2; i++) {
		#pragma HLS PIPELINE rewind
    	wtype wr; wtype wi;
    	get_twiddles1(1, i, &wr, &wi);

		int k1 = i;          // index of btfly 1st input
        int k2 = i + SIZE/2; // index of btfly 2nd input
        btfly2(xr[k1], xi[k1], xr[k2], xi[k2], wr, wi,
               &yr[k1], &yi[k1], &yr[k2], &yi[k2]);
    }
}

void fft_stage_last(dtype xr[SIZE], dtype xi[SIZE],
                    dtype yr[SIZE], dtype yi[SIZE]) {

	btfly_loop: for(int j=0; j<SIZE/2; j++) {
        #pragma HLS PIPELINE rewind

		int k1 = 2*j;    // index of btfly 1st input
        int k2 = k1 + 1; // index of btfly 2nd input
        yr[k1] = (xr[k1] + xr[k2]) / 2;
        yi[k1] = (xi[k1] + xi[k2]) / 2;
        yr[k2] = (xr[k1] - xr[k2]) / 2;
        yi[k2] = (xi[k1] - xi[k2]) / 2;
    }
}

void calanfft2(dtype xr[SIZE], dtype xi[SIZE],
               dtype yr[SIZE], dtype yi[SIZE]) {
	#pragma HLS RESOURCE variable=xr core=RAM_1P
	#pragma HLS RESOURCE variable=xi core=RAM_1P
	#pragma HLS RESOURCE variable=yr core=RAM_1P
	#pragma HLS RESOURCE variable=yi core=RAM_1P
	#pragma HLS DATAFLOW

    // array that contains the fft results in 
	// intermediate stage
    dtype arr_r[STAGES-1][SIZE];
    dtype arr_i[STAGES-1][SIZE];
	#pragma HLS ARRAY_PARTITION variable=arr_r complete dim=1
	#pragma HLS ARRAY_PARTITION variable=arr_i complete dim=1

    // do first stage on input array
    fft_stage_first(xr, xi, arr_r[0], arr_i[0]);

    // do intermediate stages
    stage_loop: for(int s=1; s<=STAGES-2; s++) {
		#pragma HLS UNROLL
    	fft_stage(s, arr_r[s-1], arr_i[s-1],
                     arr_r[s],   arr_i[s]);
    }

    // do last stage on output array
    fft_stage_last(arr_r[STAGES-2], arr_i[STAGES-2], yr, yi);
}
