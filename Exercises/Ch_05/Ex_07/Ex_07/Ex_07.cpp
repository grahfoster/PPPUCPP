#include "../../../../std_lib_facilities.h"

vector<double> quadratic(double a, double b, double c);

int main() {
	const int solution1_index = 0, solution2_index = 1;
	double a = 0, b = 0, c = 0;

	// prompt user for input
	cout << "Enter three coefficients for a quadratic equation (a, b, c): ";
	while (cin >> a >> b >> c) {
		try {
			// pass coefficients to quadratic equation
			vector<double> roots = quadratic(a, b, c);
			cout << "x1 = " << roots[solution1_index] << ", x2 = " << roots[solution2_index] << '\n';
		}
		catch (exception& e) {
			cerr << e.what() << '\n';
		}
	}
}

// calculate the roots of a quadratic equation
vector<double> quadratic(double a, double b, double c) {
	// pre-condition: coefficients create real roots
	if (b * b < 4 * a * c)
		error("quadratic() pre-condition failed: imaginary roots");
	// pre-condition: coefficients create non-infinite roots
	if (a == 0)
		error("quadratic() pre-condition failed: infinite roots");

	// calculate roots
	double x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	double x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	return vector<double> {x1, x2};
}