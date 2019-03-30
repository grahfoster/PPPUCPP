#include "../../../../std_lib_facilities.h"

int main() {
	const int lower_bound = 2, upper_bound = 100;

	vector<int> numbers;

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