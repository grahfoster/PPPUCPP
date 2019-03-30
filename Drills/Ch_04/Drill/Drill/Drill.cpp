#include "../../../../std_lib_facilities.h"

int main() {
	const double cm_per_m = 100, cm_per_in = 2.54, in_per_ft = 12;

	int num_vals = 0;
	double val = 0, smallest_val = 0, largest_val = 0, sum = 0;
	string unit;
	vector<double> vals;

	// collect a double value and a unit of measurement
	cout << "Enter a double value followed by a unit (cm/m/in/ft): ";
	while (cin >> val >> unit) {
		// check for valid input
		if (unit == "cm" || unit == "m" || unit == "in" || unit == "ft") {
			// convert to meters
			if (unit == "cm")
				val /= cm_per_m;
			else if (unit == "in")
				val *= cm_per_in / cm_per_m;
			else if (unit == "ft")
				val *= in_per_ft * cm_per_in / cm_per_m;

			// output converted value
			cout << val << "m";

			// indicate if value is smallest or largest so far
			if (num_vals == 0) {	// if first value, suppress additional message
				smallest_val = val;
				largest_val = val;
				cout << endl;
			}
			else if (val < smallest_val) {
				smallest_val = val;
				cout << " is the smallest value so far.\n";
			}
			else if (val > largest_val) {
				largest_val = val;
				cout << " is the largest value so far.\n";
			}
			else
				cout << endl;

			// add value to vector, increase sum of values, and increment number of values
			vals.push_back(val);
			sum += val;
			++num_vals;
		}
		else
			cout << "Invalid unit.\n";
	}

	cout << "Smallest vlue: " << smallest_val << endl
		<< "Largest value: " << largest_val << endl
		<< "Number of values: " << num_vals << endl
		<< "Sum of values: " << sum << "m\n"
		<< "Values entered: ";

	// sort vector and output values in ascending order
	sort(vals.begin(), vals.end());
	for (int i = 0; i < vals.size(); ++i)
		cout << vals[i] << "m ";
	cout << endl;
}