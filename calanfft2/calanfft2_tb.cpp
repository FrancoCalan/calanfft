#include <fstream>
#include "calanfft2.h"

// creating variables
dtype yr[SIZE], yi[SIZE];
dtype xr_tb[SIZE], xi_tb[SIZE];
float yr_tb[SIZE], yi_tb[SIZE];

int main() {
    // getting gold data
	std::ifstream gold_x;
	std::ifstream gold_y;
	gold_x.open("gold_1024_x.dat");
	gold_y.open("gold_1024_y.dat");
	for (int i=0; i<SIZE; ++i) {
        gold_x >> xr_tb[i] >> xi_tb[i];
    	gold_y >> yr_tb[i] >> yi_tb[i];
    	//printf("%f %f\n", xr_tb[i].to_float(), xi_tb[i].to_float());
    	//printf("%f %f\n", yr_tb[i], yi_tb[i]);
    }

    // perform fft
    calanfft2(xr_tb, xi_tb, yr, yi);

    // check data integrity
    float abs_error = 0.0;
    float max_error = 0.0;
    for(int i=0; i<SIZE; ++i) {
        float error = fabs(yr[i].to_float()-yr_tb[i]) + fabs(yi[i].to_float()-yi_tb[i]);
        abs_error += error;
        printf("Channel %i error: %f\n", i, error);
        if (error > max_error) {
            max_error = error;
        }
    }

    printf("Average error: %f\n", abs_error/SIZE);
    printf("Max error: %f\n", max_error);

    // save the result data
    std::ofstream res;
    res.open("calanfft2_res.dat");
    for(int i=0; i<SIZE; ++i) {
    	res << yr[i] << " " << yi[i] << "\n";
    }
    res.close();

    if ((abs_error/SIZE) > 0.00005 || max_error > 0.0001) { // This is somewhat arbitrary.  Should do proper error analysis.
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
