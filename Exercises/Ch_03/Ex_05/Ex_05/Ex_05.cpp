#include "../../../../std_lib_facilities.h"

int main() {
	double val1 = 0, val2 = 0;

	// collect data from user
	cout << "Enter two double values: ";

	// output summary of data
	while (cin >> val1 >> val2) {
		cout << "Largest: " << (val1 > val2 ? val1 : val2) << endl
			<< "Smallest: " << (val1 < val2 ? val1 : val2) << endl
			<< "Sum: " << val1 + val2 << endl
			<< "Difference: " << abs(val1 - val2) << endl
			<< "Product: " << val1 * val2 << endl
			<< "Quotient: " << val1 / val2 << endl;
	}
}