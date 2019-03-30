#include "../../../../std_lib_facilities.h"

int main() {
	const int first_prime = 2;

	bool is_prime = true;
	int num_primes = 0;

	// prompt user for input
	cout << "Enter a number of prime numbers to calculate: ";
	while (cin >> num_primes) {
		vector<int> prime_nums;

		// check for invalid input
		if (num_primes <= 0) {
			cout << "Number must be positive.\n";
			continue;
		}

		// check each value between 1 and 100 to see if it is prime
		for (int i = first_prime; prime_nums.size() < num_primes; ++i) {
			if (prime_nums.size() > 0) {
				for (int j = 0; j < prime_nums.size(); ++j) {
					// track if the number isn't prime
					if (i % prime_nums[j] == 0)
						is_prime = false;
				}
			}
			// if the number is prime, add it to the vector
			if (is_prime)
				prime_nums.push_back(i);

			is_prime = true;
		}

		// print all prime numbers found
		cout << "First " << num_primes << " prime numbers: ";
		for (int i = 0; i < prime_nums.size(); ++i)
			cout << prime_nums[i] << " ";
		cout << endl;
	}
}