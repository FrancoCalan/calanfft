#include "twiddles_loop.h"

void twiddles_loop(dtype xr[SIZE], dtype xi[SIZE],
                   dtype yr[SIZE], dtype yi[SIZE]) {
	#pragma HLS RESOURCE variable=xr core=RAM_1P
	#pragma HLS RESOURCE variable=xi core=RAM_1P
	#pragma HLS RESOURCE variable=yr core=RAM_1P
	#pragma HLS RESOURCE variable=yi core=RAM_1P

    int n = 1 << STAGE;    //number of stage subffts
    int m = SIZE >> STAGE; // size of stage subffts

    twiddles_loop: for(int i=0; i<m/2; ++i) {
    	wtype wr; wtype wi;
        get_twiddles1(n, i, &wr, &wi);

		btfly_loop: for(int j=0; j<n; ++j) {
        	#pragma HLS PIPELINE rewind
			int k1 = j*m + i;  // index of btfly 1st input
        	int k2 = k1 + m/2; // index of btfly 2nd input
            btfly2(xr[k1], xi[k1], xr[k2], xi[k2], wr, wi,
                   &yr[k1], &yi[k1], &yr[k2], &yi[k2]);
        }
    }
}
