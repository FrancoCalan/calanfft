#include <stdio.h>
#include <fstream>
#include <math.h>
#include "twiddles_loop.h"

// creating variables
dtype yr[SIZE],    yi[SIZE];
dtype xr_tb[SIZE], xi_tb[SIZE];
dtype yr_tb[SIZE], yi_tb[SIZE];

int main() {
    // getting gold data
    std::ifstream gold_x("gold_x-20200615-180101.dat");
    std::ifstream gold_y("gold_y-20200615-180101.dat");
    for (int i=0; i<SIZE; ++i) {
        gold_x >> xr_tb[i] >> xi_tb[i];
        gold_y >> yr_tb[i] >> yi_tb[i];
    }
    
    // perform twiddles loop
    twiddles_loop(xr_tb, xi_tb, yr, yi);
    
    // check data integrity
    dtype abs_error = 0.0;
    dtype max_error = 0.0;
    for(int i=0; i<SIZE; ++i) {
        error = fabs(yr[i]-yr_tb[i]) + fabs(yi[i]-yi_tb[i]);
        if (error > maxerror) {
            max_error = error;
        }
    }
    
    fprintf(stdout, "Average Error: %f\n", abs_error/SIZE);
    fprintf(stdout, "Max Error: %f\n", max_error);

    return 0;
}
