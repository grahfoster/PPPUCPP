#include "../../../../std_lib_facilities.h"

double ctok(double c);

const double d = 273.15;	// degrees Celsius/Kelvin difference

int main() {
	double c = 0;	// declare input variable
	cin >> c;	// retrieve temperature to input variable
	try {
		if (c < -d)	// check if tempurature is valid (above 0 degrees Kelvin)
			error("ctok() pre-condition");
		cout << ctok(c) << '\n';	// print out converted temperature
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
}

// convert degrees Celsius to Kelvin
double ctok(double c) {
	return c + d;
}