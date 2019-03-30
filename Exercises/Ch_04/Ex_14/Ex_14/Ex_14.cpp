#include "../../../../std_lib_facilities.h"

int main() {
	const int lower_bound = 2;

	int upper_bound = 0;

	// prompt the user to enter an upper bound
	cout << "Enter an upper bound: ";
	while (cin >> upper_bound) {
		vector<int> numbers;

		// check for invalid input
		if (upper_bound < lower_bound) {
			cout << "Value must be larger than the first prime number (2).\n";
			continue;
		}

		// load vector with all numbers in specified range
		for (int i = lower_bound; i < upper_bound; ++i)
			numbers.push_back(i);

		// use Sieve of Eratosthenes to remove non-prime numbers from vector
		for (int i = 0; i < numbers.size(); ++i) {
			for (int j = 0; j < numbers.size(); ++j) {
				for (int k = lower_bound; numbers[i] * k < upper_bound; ++k) {
					if (numbers[j] == numbers[i] * k)
						numbers.erase(numbers.begin() + j);
				}
			}
		}

		// print all prime numbers found
		cout << "Prime numbers between 1 and " << upper_bound << ": ";
		for (int i = 0; i < numbers.size(); ++i)
			cout << numbers[i] << " ";
		cout << endl;
	}
}