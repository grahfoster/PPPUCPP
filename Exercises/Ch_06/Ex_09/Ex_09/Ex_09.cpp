#include "../../../../std_lib_facilities.h"

int to_int(char c);

int main() {
	const int max_digits = 4;

	char digit = 0;
	vector<int> converted_digits;

	cout << "Enter a number up to " << max_digits << " digits long.\n"
		<< "Type '|' to terminate input.\n";
	try {
		while (cin >> digit) {
			if (digit == '|')	// handle terminating input
				break;
			if (!isdigit(digit))	// handle non-digit input
				error("Not a number.\n");

			converted_digits.push_back(to_int(digit));	// convert character digits to integers

			if (converted_digits.size() > max_digits)	// handle too-long input
				error("Number is too long.\n");
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Unexpected error.\n";
		return 2;
	}

	for (int i : converted_digits)
		cout << i;
	cout << " is ";
	
	int tens_place = 0;
	switch(converted_digits.size()) {	// output converted digits
	case max_digits:
		cout << converted_digits[tens_place] << (converted_digits[tens_place] == 1 ? " thousand and " : " thousands and ");
		++tens_place;
	case max_digits - 1:
		cout << converted_digits[tens_place] << (converted_digits[tens_place] == 1 ? " hundred and " : " hundreds and ");
		++tens_place;
	case max_digits - 2:
		cout << converted_digits[tens_place] << (converted_digits[tens_place] == 1 ? " ten and " : " tens and ");
		++tens_place;
	case max_digits - 3:
		cout << converted_digits[tens_place] << (converted_digits[tens_place] == 1 ? " one.\n" : " ones.\n");
	}
}

int to_int(char c) {
	return c - '0';
}