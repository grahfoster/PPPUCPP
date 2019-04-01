#include "../../../../std_lib_facilities.h"

double ctof(double c);
double ftoc(double f);

const double r = 1.8;	// Celsius/Fahrenheit degree ratio
const double d = 32;	// Celsius/Fahrenheit degree difference
const double k = 273.15;	// Celsius/Kelvin degree difference

int main() {
	string unit;
	double degrees = 0;

	cout << "Enter a temperature to convert followed by its unit (c/celsius/f/fahrenheit): ";
	while (cin >> degrees >> unit) {	// retrieve temperature to input variables
		// check for valid unit
		if (unit != "c" && unit != "celsius" && unit != "f" && unit != "fahrenheit") {
			cout << "Invalid unit.\n";
			continue;
		}
		try {
			// print out converted temperature
			cout << (unit == "c" || unit == "celsius" ? ctof(degrees) : ftoc(degrees))
				<< (unit == "c" || unit == "celsius" ? 'f' : 'c') << '\n';
		}
		catch (exception& e) {
			cerr << e.what() << '\n';
		}
	}

	if (!cin)
		cerr << "Invalid input.\n";
}

// convert degrees Celsius to Fahrenheit
double ctof(double c) {
	// pre-condition: temperature is above 0 degrees Kelvin
	if (c < -k)
		error("ctof() pre-condition");

	return narrow_cast<int>(c * r + d);
}

// convert degrees Fahrenheit to Celsius
double ftoc(double f) {
	// pre-condition: temperature is above 0 degrees Kelvin
	if ((f - d) / r < -k)
		error("ftoc() pre-condition");

	return narrow_cast<int>((f - d) / r);
}