#include "../../../../std_lib_facilities.h"

int main() {
	const double km_per_mile = 1.609;
	double miles = 0;

	// collect user input and output converted value
	cout << "Enter a number of miles to convert to kilometers: ";
	cin >> miles;
	cout << miles << (miles == 1 ? " mile" : " miles") << " equals " << miles * km_per_mile << " kilometers.\n";
}