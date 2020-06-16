#include <fstream>
#include "twiddles_loop.h"

// creating variables
dtype yr[SIZE], yi[SIZE];
dtype xr_tb[SIZE], xi_tb[SIZE];
float yr_tb[SIZE], yi_tb[SIZE];

int main() {
    // getting gold data
	std::ifstream gold_x("gold_x-20200616-123935.dat");
    std::ifstream gold_y("gold_y-20200616-123935.dat");
    for (int i=0; i<SIZE; ++i) {
        gold_x >> xr_tb[i] >> xi_tb[i];
    	gold_y >> yr_tb[i] >> yi_tb[i];
        //printf("%f\t%f\n", xr_tb[i].to_float(), xi_tb[i].to_float());
    	//printf("%f\t%f\n", yr_tb[i], yi_tb[i]);
    }

    // perform twiddles loop
    twiddles_loop(xr_tb, xi_tb, yr, yi);

    // check data integrity
    float abs_error = 0.0;
    float max_error = 0.0;
    for(int i=0; i<SIZE; ++i) {
        float error = fabs(yr[i].to_float()-yr_tb[i]) + fabs(yi[i].to_float()-yi_tb[i]);
        //float error = fabs(yr[i].to_float()-yr_tb[i]/2) + fabs(yi[i].to_float()-yi_tb[i]/2);
        //float error = fabs(yr[i]-yr_tb[i]) + fabs(yi[i]-yi_tb[i]);
        abs_error += error;
        //printf("Channel %i error: %f\n", i, error);
        if (error > 0.1){
        	printf("Large error at channel %i\n", i);
        	printf("yr: %f\n", yr[i].to_float());
        	printf("yi: %f\n", yi[i].to_float());
        	printf("yr_tb: %f\n", yr_tb[i]);
        	printf("yi_tb: %f\n", yi_tb[i]);
        }
        if (error > max_error) {
            max_error = error;
        }
    }

    fprintf(stdout, "Average error: %f\n", abs_error/SIZE);
    fprintf(stdout, "Max error: %f\n", max_error);

    // save the result data
    std::ofstream res;
    res.open("twiddles_loop_res.dat");
    for(int i=0; i<SIZE; ++i) {
    	res << yr[i] << " " << yi[i] << "\n";
    }
    res.close();

    if ((abs_error/SIZE) > .05 || max_error > 2) { // This is somewhat arbitrary.  Should do proper error analysis.
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
    	fprintf(stdout, "*******************************************\n");
    	return 1;
    } else {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "PASS: The output matches the golden output!\n");
    	fprintf(stdout, "*******************************************\n");
    	return 0;
    }
    return 0;
}
