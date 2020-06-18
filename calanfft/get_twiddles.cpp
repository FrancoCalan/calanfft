#include "calanfft.h"

void get_twiddles1(int n, int i, wtype *wr, wtype *wi) {
    *wr = wr_arr[i*n];
    *wi = wi_arr[i*n];
}
