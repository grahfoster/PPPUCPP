#include "../../../../std_lib_facilities.h"

double ctok(double c);
double ktoc(double k);

const double d = 273.15;	// Celsius/Kelvin degree difference

int main() {
	string unit;
	double degrees = 0;

	cout << "Enter a temperature to convert followed by its unit (c/celsius/k/kelvin): ";
	while (cin >> degrees >> unit) {	// retrieve temperature to input variables
		// check for valid unit
		if (unit != "c" && unit != "celsius" && unit != "k" && unit != "kelvin") {
			cout << "Invalid unit.\n";
			continue;
		}
		try {
			// print out converted temperature
			cout << (unit == "c" || unit == "celsius" ? ctok(degrees) : ktoc(degrees))
				<< (unit == "c" || unit == "celsius" ? 'k' : 'c') << '\n';
		}
		catch (exception& e) {
			cerr << e.what() << '\n';
		}
	}

	if (!cin)
		cerr << "Invalid input.\n";
}

// convert degrees Celsius to Kelvin
double ctok(double c) {
	// pre-condition: temperature is above 0 degrees Kelvin
	if (c < -d)
		error("ctok() pre-condition");
	return c + d;
}

// convert degrees Kelvin to Celsius
double ktoc(double k) {
	// pre-condition: temperature is above 0 degrees Kelvin
	if (k < 0)
		error("ktoc() pre-condition");
	return k - d;
}