#include <fstream>
#include "twiddles_loop.h"

// creating variables
dtype yr[SIZE], yi[SIZE];
dtype xr_tb[SIZE], xi_tb[SIZE];
float yr_tb[SIZE], yi_tb[SIZE];

int main() {
    // getting gold data
	std::ifstream gold_x;
	std::ifstream gold_y;
	if (STAGE == 0) {
		gold_x.open("gold_x-20200616-123935.dat");
		gold_y.open("gold_y-20200616-123935.dat");
	} else if (STAGE == 5) {
		gold_x.open("gold_x-20200616-162454.dat");
		gold_y.open("gold_y-20200616-162454.dat");
	} else if (STAGE == 9){
		gold_x.open("gold_x-20200616-163213.dat");
		gold_y.open("gold_y-20200616-163213.dat");
	}

	for (int i=0; i<SIZE; ++i) {
        gold_x >> xr_tb[i] >> xi_tb[i];
    	gold_y >> yr_tb[i] >> yi_tb[i];
    }

    // perform twiddles loop
    twiddles_loop(xr_tb, xi_tb, yr, yi);

    // check data integrity
    float abs_error = 0.0;
    float max_error = 0.0;
    for(int i=0; i<SIZE; ++i) {
        float error = fabs(yr[i].to_float()-yr_tb[i]/2) + fabs(yi[i].to_float()-yi_tb[i]/2);
        abs_error += error;
        printf("Channel %i error: %f\n", i, error);
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
