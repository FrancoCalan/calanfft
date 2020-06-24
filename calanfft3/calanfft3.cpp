#include "calanfft3.h"
#include <math.h>

void fft_stage(int stage,
               dtype xr[SIZE], dtype xi[SIZE],
			   wtype wrs,      wtype wis,
               dtype yr[SIZE], dtype yi[SIZE]) {
    int n = 1 << stage;    //number of stage subffts
    int m = SIZE >> stage; // size of stage subffts
    wtype wr = 1;
    wtype wi = 0;

    twiddles_loop: for(int i=0; i<m/2; i++) {
    	btfly_loop: for(int j=0; j<n; j++) {
        	#pragma HLS PIPELINE

			int k1 = j*m + i;  // index of btfly 1st input
        	int k2 = k1 + m/2; // index of btfly 2nd input
        	int k3  = n*i;      // index of twiddle factor
            btfly2(xr[k1], xi[k1], xr[k2], xi[k2],
            	   wr,     wi,
                   &yr[k1], &yi[k1], &yr[k2], &yi[k2]);
        }
    	// update twiddle
    	twiddle_mtply(&wr, &wi, wrs, wis);
    }
}

void fft_stage_first(dtype xr[SIZE], dtype xi[SIZE],
				     wtype wrs,      wtype wis,
                     dtype yr[SIZE], dtype yi[SIZE]) {

	wtype wr = 1;
	wtype wi = 0;

    twiddles_loop: for(int i=0; i<SIZE/2; i++) {
		#pragma HLS PIPELINE rewind

		int k1 = i;          // index of btfly 1st input
        int k2 = i + SIZE/2; // index of btfly 2nd input
        btfly2(xr[k1], xi[k1], xr[k2], xi[k2],
        	   wr,  wi,
               &yr[k1], &yi[k1], &yr[k2], &yi[k2]);
        // update twiddle
        twiddle_mtply(&wr, &wi, wrs, wis);
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

void calanfft3(dtype xr[SIZE], dtype xi[SIZE],
               dtype yr[SIZE], dtype yi[SIZE]) {
	#pragma HLS RESOURCE variable=xr core=RAM_1P
	#pragma HLS RESOURCE variable=xi core=RAM_1P
	#pragma HLS RESOURCE variable=yr core=RAM_1P
	#pragma HLS RESOURCE variable=yi core=RAM_1P
	#pragma HLS DATAFLOW

	// generate twiddle steps
	static wtype wr_arr[STAGES-1];
	static wtype wi_arr[STAGES-1];
	for(int i=0; i<STAGES-1; i++) {
		int m = SIZE >> i; // size of stage subfft
		wr_arr[i] = cos(-2*M_PI/m);
		wi_arr[i] = sin(-2*M_PI/m);
		//printf("%f, %f\n", wr_arr[i].to_float(), wi_arr[i].to_float());
	}
	#pragma HLS ARRAY_PARTITION variable=wr_arr complete dim=1
	#pragma HLS ARRAY_PARTITION variable=wi_arr complete dim=1

    // array that contains the fft results in 
	// intermediate stage
    static dtype sr_arr[STAGES-1][SIZE];
    static dtype si_arr[STAGES-1][SIZE];
	#pragma HLS ARRAY_PARTITION variable=sr_arr complete dim=1
	#pragma HLS ARRAY_PARTITION variable=si_arr complete dim=1

    // do first stage on input array
    fft_stage_first(xr, xi,
    				wr_arr[0], wi_arr[0],
					sr_arr[0], si_arr[0]);

    // do intermediate stages
    stage_loop: for(int s=1; s<=STAGES-2; s++) {
		#pragma HLS UNROLL
    	fft_stage(s, sr_arr[s-1], si_arr[s-1],
					 wr_arr[s],   wi_arr[s],
    				 sr_arr[s],   si_arr[s]);
    }

    // do last stage on output array
    fft_stage_last(sr_arr[STAGES-2], si_arr[STAGES-2],
    		       yr, yi);
}
