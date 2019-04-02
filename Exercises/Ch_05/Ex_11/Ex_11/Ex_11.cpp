#include "../../../../std_lib_facilities.h"

int main() {
	int num_values = 0;
	vector<int> fibonacci_values;

	cout << "Enter the number of Fibonacci values to display: ";
	cin >> num_values;
	if (!cin) {	// reject non-integer input
		cerr << "Invalid input.\n";
		return 1;
	}

	for (int i = 0; fibonacci_values.size() < num_values; ++i) {
		const int int_max = 65535;	// largest value of an int
		double fibonacci_value = fibonacci_values.size() < 2 ? 1	// don't try to access out-of-range values
			: fibonacci_values[i - 1] + fibonacci_values[i - 2];	// add the previous two values
		
		try {
			if (fibonacci_value > int_max)	// check if number can fit in an int
				error("too large to express as int");
			fibonacci_values.push_back(fibonacci_value);	// add value to vector
			cout << fibonacci_value << ' ';	// output values
		}
		catch (exception& e) {
			cerr << e.what() << ' ';
			return 2;
		}
	}

	cout << '\n';
}