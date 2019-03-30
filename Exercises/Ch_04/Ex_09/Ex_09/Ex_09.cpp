#include "../../../../std_lib_facilities.h"

int main() {
	const int num_squares = 64, benchmark1 = 1000, benchmark2 = 1000000, benchmark3 = 1000000000;

	bool benchmark1_reached = false, benchmark2_reached = false, benchmark3_reached = false;
	int current_square = 0;
	double grains = 0;

	for (int i = 0; i < num_squares; ++i) {
		// update the current square and total grains
		current_square = i + 1;
		grains += pow(2, i);

		cout << "Current square: " << current_square << "\tTotal grains: " << grains << endl;

		// indicate if a benchmark has been reached
		if (benchmark3_reached == false && grains >= benchmark3) {
			cout << benchmark3 << " grains reached!\n";
			benchmark3_reached = true;
		}
		else if (benchmark2_reached == false && grains >= benchmark2) {
			cout << benchmark2 << " grains reached!\n";
			benchmark2_reached = true;
		}
		else if (benchmark1_reached == false && grains >= benchmark1) {
			cout << benchmark1 << " grains reached!\n";
			benchmark1_reached = true;
		}
	}
}