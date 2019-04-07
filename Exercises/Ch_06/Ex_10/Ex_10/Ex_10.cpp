#include "../../../../std_lib_facilities.h"

void set_vals();
void set_operator();
void calculate_permutations();
void calculate_combinations();
int factorial(int val);

char operation = 0;
int a = 0, b = 0, result = 0;

int main() {
	try {
		set_vals();
		set_operator();
		if (operation == 'p')
			calculate_permutations();
		else if (operation == 'c')
			calculate_combinations();
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << ".\n";
		return 1;
	}
	catch (...) {
		cerr << "Unexpected error.\n";
		return 2;
	}

	cout << "Number of possible " << (operation == 'p' ? "permutations: " : "combinations: ") << result;
}

// set the values to be used in the calculation
void set_vals() {
	cout << "Enter two integer values.\n";
	cin >> a >> b;
	if (!cin)	// handle non-integer input
		error("value is not an integer");
	if (a <= 0 || b <= 0)	// handle non-positive input
		error("non-positive integer");
	if (a < b)
		error("sample size larger than number of objects");
}

// set whether to calculate permutations or combinations
void set_operator() {
	cout << "Choose an operation to perform ('p' for permutations, 'c' for combinations).\n";
	cin >> operation;
	if (!cin || (operation != 'p' && operation != 'c'))	// handle illegal operators
		error("illegal operator");
}

// calculate the number of possible permutations
void calculate_permutations() {
	result = factorial(a) / factorial(a - b);
}

// calculate the number of possible combinations
void calculate_combinations() {
	calculate_permutations();
	result /= factorial(b);
}

// calculate the factorial of a given value
int factorial(int val) {
	double factorial = val;

	if (factorial == 0)	// 0! is 1
		return 1;
	for (int i = 1; i < val; ++i)
		factorial *= i;
	return narrow_cast<int>(factorial);	// try to cast double as int
}