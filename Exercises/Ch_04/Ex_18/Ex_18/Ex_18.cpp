#include "../../../../std_lib_facilities.h"

int main() {
	double a = 0, b = 0, c = 0;

	// prompt user for input
	cout << "Enter three coefficients for a quadratic equation (a, b, c): ";
	while (cin >> a >> b >> c) {
		// outpute solutions if real
		if (b * b > 4 * a * c)
			cout << "x1 = " << (-b + sqrt(b * b - 4 * a * c)) / (2 * a) << "\t"
			<< "x2 = " << (-b - sqrt(b * b - 4 * a * c)) / (2 * a) << "\n";
		else
			cout << "No real solutions.\n";
	}
}