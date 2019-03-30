#include "../../../../std_lib_facilities.h"

int main() {
	int number = 50, lower_bound = 1, higher_bound = 100;
	char response = 0;

	cout << "Think of a number between 1 and 100. Enter y or n to confirm or deny computer questions.\n";
	cout << "Is your number less than " << number << "?\n";

	while (cin >> response) {
		// check for invalid input
		if (response != 'y' && response != 'n')
			cout << "Enter y or n to confirm or deny computer questions.\n";

		// narrow down the range of values depending on user input
		if (response == 'y') {
			higher_bound = number - 1;
			if (higher_bound - lower_bound < 2)
				number -= 1;
			else
				number -= (higher_bound - lower_bound) / 2;
		}
		else if (response == 'n') {
			lower_bound = number;
			if (higher_bound - lower_bound < 2)
				number += 1;
			else
				number += (higher_bound - lower_bound) / 2;
		}

		// if the range of values is 1, tell the user their number, otherwise keep asking
		if (lower_bound == higher_bound) {
			cout << "I've got it! Your number is " << lower_bound << endl;
			return 0;
		}
		else
			cout << "Is your number less than " << number << "?\n";
	}
}