#include "twiddles_loop.h"

void twiddles_loop(dtype xr[SIZE], dtype xi[SIZE],
                   dtype yr[SIZE], dtype yi[SIZE]) {
	#pragma HLS RESOURCE variable=xr core=RAM_1P
	#pragma HLS RESOURCE variable=xi core=RAM_1P
	#pragma HLS RESOURCE variable=yr core=RAM_1P
	#pragma HLS RESOURCE variable=yi core=RAM_1P

    int n = 10 << STAGE;    //number of stage subffts
    int m = SIZE >> STAGE; // size of stage subffts

    twiddles_loop: for(int i=0; i<m/2; ++i) {
        wtype wr; wtype wi;
        get_twiddles1(n, i, &wr, &wi);

        btfly_loop: for (int j1=0; j1<SIZE; j1+=m) {
			#pragma HLS PIPELINE rewind
        	int j2 = j1 + m/2; // index of btfly 2nd input
            btfly2(xr[j1], xi[j1], xr[j2], xi[j2], wr, wi,
                   &yr[j1], &yi[j1], &yr[j2], &yi[j2]);
        }
    }
}
