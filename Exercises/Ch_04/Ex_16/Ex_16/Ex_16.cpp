#include "../../../../std_lib_facilities.h"

int main() {
	int value = 0, repeats = 0, most_repeats = 0, mode = 0;
	vector<int> values;

	// prompt user for input
	cout << "Enter a sequence of integers: ";
	while (cin >> value) {
		values.push_back(value);
		for (int i = 0; i < values.size(); ++i) {
			// set new mode
			if (value == values[i])
				++repeats;
			if (repeats > most_repeats)
				mode = value;
		}
		// set counters
		most_repeats = repeats;
		repeats = 0;
	}

	// output mode
	cout << "Mode: " << mode << endl;
}