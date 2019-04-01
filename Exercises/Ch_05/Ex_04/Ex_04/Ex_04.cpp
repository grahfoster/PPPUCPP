#include "../../../../std_lib_facilities.h"

double ctok(double c);

const double d = 273.15;	// degrees Celsius/Kelvin difference

int main() {
	double c = 0;	// declare input variable
	cin >> c;	// retrieve temperature to input variable
	try {
		cout << ctok(c) << '\n';	// print out converted temperature
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
}

// convert degrees Celsius to Kelvin
double ctok(double c) {
	// pre-condition: temperature is valid (above 0 degrees Kelvin)
	if (c < -d)
		error("ctok() pre-condition");
	return c + d;
}