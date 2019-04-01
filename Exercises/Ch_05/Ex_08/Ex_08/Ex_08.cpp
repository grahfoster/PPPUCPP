#include "../../../../std_lib_facilities.h"

int main() {
	int val = 0, num_vals = 0, sum_vals = 0;
	vector<int> vals;

	cout << "Enter the number of values you want to sum: ";
	while (cin >> num_vals || num_vals <= 0) {
		if (!cin) {	// reject non-integer input
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cerr << "Please enter an integer.\n";
			continue;
		}
		else if (num_vals <= 0)	// reject non-positive integer input
			cerr << "Please enter a positive integer.\n";
		else
			break;
	}

	cout << "Enter a series of integer values: ";
	while (cin >> val || vals.size() < num_vals) {	// ask for input until vector contains desired number of values
		if (!cin) {	// reject non-integer input
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cerr << "Please enter only integer values.\n";
			continue;
		}

		vals.push_back(val);	// add value to vector
	}
	
	for (int i = 0; i < num_vals; ++i)	// calculate sum
		sum_vals += vals[i];
	cout << "Sum: " << sum_vals << '\n';	// print sum
}