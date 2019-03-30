#include "../../../../std_lib_facilities.h"

int main() {
	bool valid_input = false;
	string number;
	vector<string> spelled_numbers = {
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	// collect string from user
	cout << "Enter a digit or spelled-out number: ";
	while (cin >> number) {
		// check if string is an integer
		if (number.length() == 1) {
			for (int i = 0; i < 10; ++i) {
				if (to_string(i) == number) {
					valid_input = true;
					cout << spelled_numbers[i] << endl;
				}
			}
		}
		// check if string is a spelled-out number
		else {
			for (int i = 0; i < spelled_numbers.size(); ++i) {
				if (spelled_numbers[i] == number) {
					valid_input = true;
					cout << i << endl;
				}
			}
		}

		// indicate if input was invalid
		if (!valid_input)
			cout << "I don't know that number.\n";
		valid_input = false;
	}
}